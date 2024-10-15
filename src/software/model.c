#include "model.h"

#include "camera.h"
#include "cdrom.h"
#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>


// TODO: If texture NULL, render missing texture?
// Error check for missing model, etc
void model_renderTextured(Model *model, TextureInfo *texture, Camera *cam, uint16_t rotx, uint16_t roty, uint16_t rotz, int32_t tx, int32_t ty, int32_t tz){
    
    if(tx+cam->x > 32767 || tx+cam->x < -32768){
        return;
    }
    if(ty+cam->y > 32767 || ty+cam->y < -32768){
        return;
    }
    if(tz+cam->z > 32767 || tz+cam->z < -32768){
        return;
    }

    // Save the current translation vector
    int32_t currentTx, currentTy, currentTz;
    gte_getTranslationVector(&currentTx, &currentTy, &currentTz);
    // Save the Current Rotation Matrix
    GTEMatrix crm;
    gte_storeRotationMatrix(&crm);
    
    // Translate model
    updateTranslationMatrix(tx+cam->x, ty+cam->y, tz+cam->z);
    // Rotate model
    rotateCurrentMatrix(rotx, roty, rotz);
    
    // Add every triangle to the ordering table for rendering.
    for(int i = 0; i<model->numTris; i++){

        GTEVector16 a, b, c;
        a.x = (model->verts[model->tris[i].a].x);
        a.y = (model->verts[model->tris[i].a].y);
        a.z = (model->verts[model->tris[i].a].z);

        b.x = (model->verts[model->tris[i].b].x);
        b.y = (model->verts[model->tris[i].b].y);
        b.z = (model->verts[model->tris[i].b].z);

        c.x = (model->verts[model->tris[i].c].x);
        c.y = (model->verts[model->tris[i].c].y);
        c.z = (model->verts[model->tris[i].c].z);

        

        gte_loadV0(&a);
        gte_loadV1(&b);
        gte_loadV2(&c);


        gte_command(GTE_CMD_RTPT | GTE_SF);
        gte_command(GTE_CMD_NCLIP);

        // If the face is facing away from us, don't bother rendering it.
        if(gte_getMAC0() <= 0){
            continue;
        }

        // Calculate the average Z value of all 3 verts.
        gte_command(GTE_CMD_AVSZ3 | GTE_SF);
        int zIndex = gte_getOTZ();

        // If too close/behind camera, don't render
        if(zIndex <= 0){
            continue;
        }
        
        // Don't render things too far away.
        if(zIndex >= ORDERING_TABLE_SIZE){
            continue;
        }

        // Calculate the texture UV coords for the verts in this face.
        uint32_t uv0 = gp0_uv((uint32_t)(texture->u + model->tris[i].auv) >> 8, (uint32_t)((uint32_t)texture->v + (uint32_t)model->tris[i].auv) & 0x00FF, texture->clut);
        uint32_t uv1 = gp0_uv((uint32_t)(texture->u + model->tris[i].buv) >> 8, (uint32_t)((uint32_t)texture->v + (uint32_t)model->tris[i].buv) & 0x00FF, texture->page);
        uint32_t uv2 = gp0_uv((uint32_t)(texture->u + model->tris[i].cuv) >> 8, (uint32_t)((uint32_t)texture->v + (uint32_t)model->tris[i].cuv) & 0x00FF, 0);

        // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
        dmaPtr = allocatePacket(activeChain, zIndex, 7);
        dmaPtr[0] = 0x808080 | gp0_shadedTriangle(false, true, false);
        dmaPtr[1] = gte_getSXY0();
        dmaPtr[2] = uv0;
        dmaPtr[3] = gte_getSXY1();
        dmaPtr[4] = uv1;
        dmaPtr[5] = gte_getSXY2();
        dmaPtr[6] = uv2;
    }

    // Restore the translation and rotation back to the initial state as to not clober any other models.
    gte_setTranslationVector(currentTx, currentTy, currentTz);
    gte_setRotationMatrix(
        crm.values[0][0], crm.values[0][1], crm.values[0][2],
        crm.values[1][0], crm.values[1][1], crm.values[1][2],
        crm.values[2][0], crm.values[2][1], crm.values[2][2]
    );
};


size_t model_load(const char *name, Model *model){
    uint32_t modelLba;
    uint16_t sectorBuffer[1024];
    
    modelLba = getLbaToFile(name);
    if(!modelLba){
        // File not found
        return 1;
    }

    startCDROMRead(
        modelLba,
        sectorBuffer,
        1,
        2048,
        true,
        true
    );

    size_t sectorOffset = 0;

    uint16_t _numVerts = sectorBuffer[sectorOffset++];
    Vert *_verts = malloc(sizeof(Vert) * _numVerts);

    // For each vert
    for(int i = 0; i<_numVerts; i++){
        // For each axis
        for(int j = 0; j < 3; j++){
            // If we are reaching past the buffer
            if(sectorOffset >= 1024){
                // Read the next sector
                startCDROMRead(
                    ++modelLba,
                    sectorBuffer,
                    1,
                    2048,
                    true,
                    true
                );
                sectorOffset -= 1024;
            }
            // Copy the X, Y, then Z data into the struct, then increment the data pointer.
            ((uint16_t *) &_verts[i])[j] = sectorBuffer[sectorOffset++];
        }
    }

    // Also do the check here.
    if(sectorOffset >= 1024){
        // Read the next sector
        startCDROMRead(
            ++modelLba,
            sectorBuffer,
            1,
            2048,
            true,
            true
        );
        sectorOffset -= 1024;
    }

    uint16_t _numTris = sectorBuffer[sectorOffset++];
    Tri *_tris = malloc(sizeof(Tri) * _numTris);

    // For each triangle
    for(int i = 0; i<_numTris; i++){
        // For each vert
        for(int j = 0; j < 6; j++){
            // If we are reaching past the buffer
            if(sectorOffset >= 1024){
                // Read the next sector
                startCDROMRead(
                    ++modelLba,
                    sectorBuffer,
                    1,
                    2048,
                    true,
                    true
                );
                sectorOffset -= 1024;
            }
            // Copy the a, b, then c vert pointer into the struct. Also copy the UV coordinates.
            // Then increment the data pointer.
            ((uint16_t *) &_tris[i])[j] = sectorBuffer[sectorOffset++];
        }
    }

    model->numVerts = _numVerts;
    model->numTris = _numTris;
    model->verts = _verts;
    model->tris = _tris;

    return 0;
}

void model_destroy(Model *model){
    model->numVerts = 0;
    model->numTris = 0;
    free(model->verts);
    free(model->tris);
    model->verts = NULL;
    model->tris = NULL;
}