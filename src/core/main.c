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

/*
 * I would like to thank spicyjpeg for the ps1-bare-metal tutorial series I 
 * relied upon heavily as well as for their continued support throughout this project. 
 * The tutorial series and source code can be found at: https://github.com/spicyjpeg/ps1-bare-metal
 *
 * I would also like to extend my gratitude to the lovely people in the PSX.Dev Discord server. 
 * Without them, this project would have taken MUCH longer.
 * The PSX.Dev Discord server can be found at: https://discord.com/invite/psx-dev-642647820683444236
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "camera.h"
#include "controller.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "trig.h"
#include "cop0gte.h"
#include "gpucmd.h"
#include "registers.h"

#include "RoomModel.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256
#define FONT_WIDTH       96
#define FONT_HEIGHT      56

// 6 select colours for rendering polys in "coloured" mode
uint32_t colors[6] = {
   0x0000FF,
   0x00FF00,
   0xFF0000,
   0x00FFFF,
   0xFF00FF,
   0xFFFF00
};


void loadVerts(GTEVector32 *vertList, int *vertListLength, GTEVector32 *objectVerts, int objectVertsLength){
   for(int i = 0; i<objectVertsLength; i++){
      vertList[*vertListLength + i] = objectVerts[i];
   }
   vertListLength += objectVertsLength;
}
void loadTris(Tri_Textured *triList, int *triListLength, Tri_Textured *objectTris, int objectTrisLength){
   for(int i = 0; i<objectTrisLength; i++){
      triList[*triListLength + i] = objectTris[i];
   }
   triListLength += objectTrisLength;
}


int main(){
   initControllerBus();

   // Read the GPU's status register to check if it was left in PAL or NTSC mode by the BIOS
   if ((GPU_GP1 & GP1_STAT_MODE_BITMASK) == GP1_STAT_MODE_PAL){
      setupGPU(GP1_MODE_PAL, SCREEN_WIDTH, SCREEN_HEIGHT);
   } else {
      setupGPU(GP1_MODE_NTSC, SCREEN_WIDTH, SCREEN_HEIGHT);
   }
   // Set up the Geometry Transformation Engine with the width and height of our screen
   setupGTE(SCREEN_WIDTH, SCREEN_HEIGHT);

   // Enable the GPU's DMA channel
   DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_GPU * 4);
   DMA_DPCR |= DMA_DPCR_ENABLE << (DMA_OTC * 4);

   GPU_GP1 = gp1_dmaRequestMode(GP1_DREQ_GP0_WRITE); // Fetch GP0 commands from DMA when possible
   GPU_GP1 = gp1_dispBlank(false); // Disable display blanking

   DMAChain dmaChains[2];
   bool usingSecondFrame = false;

   
   // Include texture data files
   extern const uint8_t fontData[];
   extern const uint8_t fontPalette[];
   extern const uint8_t reference_64Data[];
   extern const uint8_t reference_64Palette[];

   // Load the font and wall textures into VRAM
   TextureInfo font;
   uploadIndexedTexture(&font, fontData, SCREEN_WIDTH+16, 0, FONT_WIDTH, FONT_HEIGHT, 
      fontPalette, SCREEN_WIDTH+16, FONT_HEIGHT, GP0_COLOR_4BPP
   );
   TextureInfo reference_64;
   uploadIndexedTexture(&reference_64, reference_64Data, SCREEN_WIDTH, 0, 64, 64,
   reference_64Palette,SCREEN_WIDTH, 64, GP0_COLOR_4BPP);

   // Used to see if the button is being held down still.
   bool trianglePressed = false;
   bool squarePressed = false;
   // We only want to update these values once per press, not per frame.
   bool showingHelp = true;
   bool renderTextured = false;
   
   // Create and initialise the camera.
   Camera camera;
   camera.x = 0;
   camera.y = -1000;
   camera.z = 0;
   camera.yaw   = 0;
   camera.roll  = 0;
   camera.pitch = 0;

   // controllerInfo will contain which buttons are pressed, etc.
   ControllerInfo controllerInfo;
   
   // Somewhere to store the Sine and Cosine of the camera's yaw value.
   // This saves us from recalculating it multiple times per frame.
   int16_t yawSin;
   int16_t yawCos;
   
   // Will hold the z value of each point on a triangle.
   // It's used later to see if any part of the triangle is visible.
   int z0, z1, z2;

   // Keep track of how many polygons are being drawn.
   int polyCount;
   
   // the X and Y of the buffer we are currently using.
   int bufferX = 0;
   int bufferY = 0;

   // The pointer to the DMA packet.
   // We allocate space for each packet before we use it.
   uint32_t *ptr;

   for(;;){
      // Point to the relevant DMA chain for this frame, then swap the active frame.
      DMAChain *chain = &dmaChains[usingSecondFrame];
      usingSecondFrame = !usingSecondFrame;

      // Reset the ordering table to a blank state.
      clearOrderingTable((chain->orderingTable), ORDERING_TABLE_SIZE);
      chain->nextPacket = chain->data;
      
      // Set the Identity Matrix.
      // Anything mutliplied by this matrix remains unchanged.
      // Its like setting the camera's rotation to its initial state.
      gte_setRotationMatrix(
         ONE,   0,   0,
         0, ONE,   0,
         0,   0, ONE
      );
      // Now we update the rotation matrix by multiplying the roll, yaw, and pitch appropriately.
      rotateCurrentMatrix(-camera.roll, camera.yaw, camera.pitch);

      // Update the translation matrix to move the camera in 3d space.
      updateTranslationMatrix(-camera.x, -camera.y, -camera.z);

      // Reset the polygon counter to 0
      polyCount = 0;

      // Iterate over every face in the model specified in RoomModel.h
      for(uint16_t i = 0; i<roomModel.faceCount; i++){
         
         const Tri_Textured *tri = &roomModel.faces[i];
         
         // Load the 3 verts into their respective V register.
         gte_loadV0(&roomModel.verts[tri->vertices[0]]);
         gte_loadV1(&roomModel.verts[tri->vertices[1]]);
         gte_loadV2(&roomModel.verts[tri->vertices[2]]);
         // Perform a perspective transformation on the 3 verts, then perform "Normal Clipping."
         gte_command(GTE_CMD_RTPT | GTE_SF);
         gte_command(GTE_CMD_NCLIP);
         // If the face is facing away from us, don't bother rendering it.
         if(gte_getMAC0() <= 0){
            continue;
         }

         // Calculate the average Z value of all 3 verts.
         gte_command(GTE_CMD_AVSZ3 | GTE_SF);
         int zIndex = gte_getOTZ();
         
         // If it is too far from the camera, clip it.
         if((zIndex >= ORDERING_TABLE_SIZE)){
            continue;
         }
         
         // If the average value is behind the camera,
         // Check if any of the corners are in view of the camera.
         // If not, skip it.
         if((zIndex <= 0)){
            //__asm__ volatile(
            //   "\tmfc2 %0, $16\n"
            //   "\tmfc2 %1, $17\n"
            //   "\tmfc2 %2, $18\n"
            //   : "=r"(z0), "=r"(z1), "=r"(z2)
            //);
            //if(z0 + z1 + z2 == 0){
               continue;
            //}
         }

         
         if(renderTextured){
            // Calculate the texture UV coords for the verts in this face.
            uint32_t uv0 = gp0_uv(reference_64.u + roomModel.faces[i].UVs[0].u, reference_64.v + roomModel.faces[i].UVs[0].v, reference_64.clut);
            uint32_t uv1 = gp0_uv(reference_64.u + roomModel.faces[i].UVs[1].u, reference_64.v + roomModel.faces[i].UVs[1].v, reference_64.page);
            uint32_t uv2 = gp0_uv(reference_64.u + roomModel.faces[i].UVs[2].u, reference_64.v + roomModel.faces[i].UVs[2].v, 0);

            // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
            ptr = allocatePacket(chain, zIndex, 7);
            ptr[0] = 0x808080 | gp0_shadedTriangle(false, true, false);
            ptr[1] = gte_getSXY0();
            ptr[2] = uv0;
            ptr[3] = gte_getSXY1();
            ptr[4] = uv1;
            ptr[5] = gte_getSXY2();
            ptr[6] = uv2;
         } else {
            // Render a triangle at the XY coords calculated via the GTE with a flat colour selected using the poly's index.
            ptr = allocatePacket(chain, zIndex, 4);
            ptr[0] = colors[i%6] | gp0_shadedTriangle(false, false, false);
            ptr[1] = gte_getSXY0();
            ptr[2] = gte_getSXY1();
            ptr[3] = gte_getSXY2();
         }
         // Increment the polygon counter as we rendered another polygon
         polyCount++;

      }

      // Print the help/debug menu
      if(showingHelp){
         char textBuffer[1024]= "\t\tControls\n======================\nL: \t \tMove\nR: \t \tLook\nL2/R2: \tDown/Up\nTriangle:\tToggle this menu\nSquare:\tToggle Textures/Colours\n";
         sprintf(textBuffer, "%s\nX:%i\nY:%i\nZ:%i\n\np: %d/%d", textBuffer, (int32_t)(camera.x), (int32_t)(camera.y), (int32_t)(camera.z), polyCount, CHAIN_BUFFER_SIZE/8);
         printString(chain, &font, 0, 0, textBuffer);
      }

      // Place the framebuffer offset and screen clearing commands last.
      // This means they will be executed first and be at the back of the screen.
      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE -1 , 3);
      ptr[0] = gp0_rgb(64, 64, 64) | gp0_vramFill();
      ptr[1] = gp0_xy(bufferX, bufferY);
      ptr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

      ptr = allocatePacket(chain, ORDERING_TABLE_SIZE - 1, 4);
      ptr[0] = gp0_texpage(0, true, false);
      ptr[1] = gp0_fbOffset1(bufferX, bufferY);
      ptr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
      ptr[3] = gp0_fbOrigin(bufferX, bufferY);


      // Check if there is a controller connected to port 0 (Port 1 on the console) and read it's info.
      if(getControllerInfo(0, &controllerInfo)){

         // Store the Sine and Cosine values for the camera's yaw as we use it multiple times
         yawSin = isin(camera.yaw);
         yawCos = icos(camera.yaw);
         
         // Up/Down
         if(controllerInfo.buttons & BUTTON_MASK_L2) camera.y += 16;
         if(controllerInfo.buttons & BUTTON_MASK_R2) camera.y -= 16;

         // If the controller type is Dualshock, read the analogue stick values to move and look around
         if(controllerInfo.type == 0x07){
            if(controllerInfo.lx>156 || controllerInfo.lx < 100){\
               camera.x += (((((controllerInfo.lx-127)) * yawCos)>>6) * MOVEMENT_SPEED)>>12;
               camera.z -= (((((controllerInfo.lx-127)) * -yawSin)>>6) * MOVEMENT_SPEED)>>12;
            }
            if(controllerInfo.ly>156 || controllerInfo.ly < 100){
               camera.x+=(((((controllerInfo.ly-127)) * yawSin)>>6) * MOVEMENT_SPEED)>>12;
               camera.z-=(((((controllerInfo.ly-127)) * yawCos)>>6) * MOVEMENT_SPEED)>>12;
            }
            if(controllerInfo.rx>156 || controllerInfo.rx < 100){
               camera.yaw -= (((controllerInfo.rx-127)>>6) * CAMERA_SENSITIVITY);
            }
            // Update camera pitch
            if(controllerInfo.ry>156 || controllerInfo.ry<100){
               camera.pitch += (((controllerInfo.ry-127)>>6) * CAMERA_SENSITIVITY);

               // Lock camera pitch to 90 degrees up or down
               if((int16_t)camera.pitch > 1024){
                  camera.pitch = 1024;
               }
               if((int16_t)camera.pitch < -1024){
                  camera.pitch = -1024;
               }
            }
         }

         // Toggle help menu only if the button isn't still being held.
         // This prevents the menu from toggling every single frame.
         if(controllerInfo.buttons & BUTTON_MASK_TRIANGLE){
            if(!trianglePressed){
               trianglePressed = true;
               showingHelp = !showingHelp;
            }
         }else{
            trianglePressed = false;
         }

         // Similar code for toggling the render type
         if(controllerInfo.buttons & BUTTON_MASK_SQUARE){
            if(!squarePressed){
               squarePressed = true;
               renderTextured = !renderTextured;
            }
         }else{
            squarePressed = false;
         }
      }

      // Wait for the GPU to finish drawing and also wait for Vsync.
      waitForGP0Ready();
      waitForVSync();

      // Swap the frame buffers.
      bufferY = usingSecondFrame ? SCREEN_HEIGHT : 0;
      GPU_GP1 = gp1_fbOffset(bufferX, bufferY); 

      // Give DMA a pointer to the last item in the ordering table.
      // We don't need to add a terminator, as it is already done for us by the OTC.
      sendLinkedList(&(chain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }

   // Stops intellisense from yelling at me.
   return 0; // 100% totally necessary.
}
