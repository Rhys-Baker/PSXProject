#include "gte.h"

#include "fixedPoint.h"
#include "gpu.h"
#include "trig.h"


void setupGTE(int width, int height) {
	// Ensure the GTE, which is coprocessor 2, is enabled. MIPS coprocessors are
	// enabled through the status register in coprocessor 0, which is always
	// accessible.
	cop0_setReg(COP0_STATUS, cop0_getReg(COP0_STATUS) | COP0_STATUS_CU2);

	// Set the offset to be added to all calculated screen space coordinates (we
	// want our cube to appear at the center of the screen) Note that OFX and
	// OFY are 16.16 fixed-point rather than 20.12.
	gte_setControlReg(GTE_OFX, (width  << 16) / 2);
	gte_setControlReg(GTE_OFY, (height << 16) / 2);

	// Set the distance of the perspective projection plane (i.e. the camera's
	// focal length), which affects the field of view.
	int focalLength = (width < height) ? width : height;

	gte_setControlReg(GTE_H, focalLength / 3);

	// Set the scaling factor for Z averaging. For each polygon drawn, the GTE
	// will sum the transformed Z coordinates of its vertices multiplied by this
	// value in order to derive the ordering table bucket index the polygon will
	// be sorted into. This will work best if the ordering table length is a
	// multiple of 12 (i.e. both 3 and 4) or high enough to make any rounding
	// error negligible.
	gte_setControlReg(GTE_ZSF3, ORDERING_TABLE_SIZE / 3);
	gte_setControlReg(GTE_ZSF4, ORDERING_TABLE_SIZE / 4);
}

// When transforming vertices, the GTE will multiply their vectors by a 3x3
// matrix stored in its registers. This matrix can be used, among other things,
// to rotate the model by multiplying it by the appropriate rotation matrices.
// The two functions below handle manipulation of this matrix.
void multiplyCurrentMatrixByVectors(GTEMatrix *output) {
	// Multiply the GTE's current matrix by the matrix whose column vectors are
	// V0/V1/V2, then store the result to the provided location. This has to be
	// done one column at a time, as the GTE only supports multiplying a matrix
	// by a vector using the MVMVA command.
	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V0 | GTE_CV_NONE);
	output->values[0][0] = gte_getDataReg(GTE_IR1);
	output->values[1][0] = gte_getDataReg(GTE_IR2);
	output->values[2][0] = gte_getDataReg(GTE_IR3);

	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V1 | GTE_CV_NONE);
	output->values[0][1] = gte_getDataReg(GTE_IR1);
	output->values[1][1] = gte_getDataReg(GTE_IR2);
	output->values[2][1] = gte_getDataReg(GTE_IR3);

	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_V2 | GTE_CV_NONE);
	output->values[0][2] = gte_getDataReg(GTE_IR1);
	output->values[1][2] = gte_getDataReg(GTE_IR2);
	output->values[2][2] = gte_getDataReg(GTE_IR3);
}



void rotateCurrentMatrix(int pitch, int roll, int yaw) {
	static GTEMatrix multiplied;
	int s, c;

	// For each axis, compute the rotation matrix then "combine" it with the
	// GTE's current matrix by multiplying the two and writing the result back
	// to the GTE's registers.
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

	if (yaw) {
		s = isin(yaw);
		c = icos(yaw);

		gte_setColumnVectors(
			c,   0, -s,
			0, ONE, 0,
		   s,   0, c
	   	);
		multiplyCurrentMatrixByVectors(&multiplied);
		gte_loadRotationMatrix(&multiplied);
	}
}

void setTranslationMatrix(int32_t x, int32_t y, int32_t z){
    int32_t tx = -x;
    int32_t ty = -y;
    int32_t tz = -z;

    gte_setDataReg(GTE_IR1, tx);
	gte_setDataReg(GTE_IR2, ty);
	gte_setDataReg(GTE_IR3, tz);
	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_IR | GTE_CV_NONE);
    
	tx = gte_getDataReg(GTE_IR1);
    ty = gte_getDataReg(GTE_IR2);
    tz = gte_getDataReg(GTE_IR3);
	gte_setControlReg(GTE_TRX, tx);
	gte_setControlReg(GTE_TRY, ty);
	gte_setControlReg(GTE_TRZ, tz);
}

void updateTranslationMatrix(int32_t x, int32_t y, int32_t z){
	int32_t tx = -x;
    int32_t ty = -y;
    int32_t tz = -z;

    gte_setDataReg(GTE_IR1, tx);
	gte_setDataReg(GTE_IR2, ty);
	gte_setDataReg(GTE_IR3, tz);
	gte_command(GTE_CMD_MVMVA | GTE_SF | GTE_MX_RT | GTE_V_IR | GTE_CV_NONE);
    
	tx = gte_getDataReg(GTE_IR1);
    ty = gte_getDataReg(GTE_IR2);
    tz = gte_getDataReg(GTE_IR3);
	gte_setControlReg(GTE_TRX, gte_getControlReg(GTE_TRX) + tx);
	gte_setControlReg(GTE_TRY, gte_getControlReg(GTE_TRY) + ty);
	gte_setControlReg(GTE_TRZ, gte_getControlReg(GTE_TRZ) + tz);
}