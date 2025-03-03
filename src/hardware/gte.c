/*
 * (C) 2024 Rhys Baker, spicyjpeg
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "fixedPoint.h"
#include "gpu.h"
#include "gte.h"
#include "trig.h"


void setupGTE(int width, int height){
    // Enable the GTE (coprocessor 2)
    cop0_setSR(cop0_getSR() | COP0_SR_CU2);

    // Set the offset for all calculated coordinates
    // Also set the FOV
    gte_setXYOrigin(width / 2, height / 2);
    gte_setFieldOfView(width);

    gte_setZScaleFactor((ONE * ORDERING_TABLE_SIZE) / 0x7fff);
}

void multiplyCurrentMatrixByVectors(GTEMatrix *output) {
    gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V0 | GTE_CV_NONE);
	output->values[0][0] = gte_getIR1();
	output->values[1][0] = gte_getIR2();
	output->values[2][0] = gte_getIR3();

	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V1 | GTE_CV_NONE);
	output->values[0][1] = gte_getIR1();
	output->values[1][1] = gte_getIR2();
	output->values[2][1] = gte_getIR3();

	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V2 | GTE_CV_NONE);
	output->values[0][2] = gte_getIR1();
	output->values[1][2] = gte_getIR2();
	output->values[2][2] = gte_getIR3();
}



void rotateCurrentMatrix(int pitch, int roll, int yaw){
    GTEMatrix multiplied;
    int s, c;
	if (pitch) {
		s = isin(pitch);
		c = icos(pitch);

		gte_setColumnVectors(
			ONE, 0,  0,
			  0, c, -s,
			  0, s,  c
		);
		multiplyCurrentMatrixByVectors(&multiplied);
		gte_loadRotationMatrix(&multiplied);
	}

	if (roll) {
		s = isin(roll);
		c = icos(roll);
		gte_setColumnVectors(
			c, -s,   0,
			s,  c,   0,
			0,  0, ONE
		);

		multiplyCurrentMatrixByVectors(&multiplied);
		gte_loadRotationMatrix(&multiplied);
	}

	if (yaw) {
		s = isin(yaw);
		c = icos(yaw);

		gte_setColumnVectors(
			 c,   0, s,
			 0, ONE, 0,
			-s,   0, c
		);
		multiplyCurrentMatrixByVectors(&multiplied);
		gte_loadRotationMatrix(&multiplied);
	}

	
}

void setTranslationMatrix(int32_t x, int32_t y, int32_t z){
    int32_t tx = -x;
    int32_t ty = -y;
    int32_t tz = -z;

    #define GTE_SET(reg, input) \
     __asm__ volatile("mtc2 %0, $%1\n" :: "r"(input), "i"(reg))
    GTE_SET(GTE_IR1, tx);
    GTE_SET(GTE_IR2, ty);
    GTE_SET(GTE_IR3, tz);
	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_IR | GTE_CV_NONE);
    
	tx = gte_getIR1();
    ty = gte_getIR2();
    tz = gte_getIR3();
	gte_setTranslationVector(tx, ty, tz);
}

void updateTranslationMatrix(int32_t x, int32_t y, int32_t z){
	int32_t tx = -x;
    int32_t ty = -y;
    int32_t tz = -z;

	int32_t ctx;
	int32_t cty;
	int32_t ctz;

    #define GTE_SET(reg, input) \
     __asm__ volatile("mtc2 %0, $%1\n" :: "r"(input), "i"(reg))
    GTE_SET(GTE_IR1, tx);
    GTE_SET(GTE_IR2, ty);
    GTE_SET(GTE_IR3, tz);
	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_IR | GTE_CV_NONE);
    
	tx = gte_getIR1();
    ty = gte_getIR2();
    tz = gte_getIR3();
	gte_getTranslationVector(&ctx, &cty, &ctz);
	gte_setTranslationVector(ctx + tx, cty + ty, ctz + tz);
}