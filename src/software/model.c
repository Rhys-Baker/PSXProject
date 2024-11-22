#include "model.h"

#include "camera.h"
#include "cdrom.h"
#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

int numPrims = 0;

int maxNumVerts = 0;

typedef struct Vector2_16{
    int16_t x, y;
} Vector2_16;

typedef struct Tri3D{
    GTEVector16 *a, *b, *c;
    uint8_t au, av;
    uint8_t bu, bv;
    uint8_t cu, cv;
} Tri3D;

typedef struct Tri2D{
    Vector2_16 a, b, c;
    uint8_t au, av;
    uint8_t bu, bv;
    uint8_t cu, cv;
} Tri2D;

TransformedVert *transformedVerts;


// Recursive Screen-space subdivisions.
// This doesn't do anything to help with texture warping, it just prevents triangles
// from disappearing when you get too close.
void recursiveSubdivideAndRender(Tri2D *_tri, TextureInfo *texture, int zIndex, int maxiterations){
    int16_t maxX = (int16_t)max((int)_tri->a.x, max((int)_tri->b.x, (int)_tri->c.x));
    int16_t maxY = (int16_t)max((int)_tri->a.y, max((int)_tri->b.y, (int)_tri->c.y));
    int16_t minX = (int16_t)min((int)_tri->a.x, min((int)_tri->b.x, (int)_tri->c.x));
    int16_t minY = (int16_t)min((int)_tri->a.y, min((int)_tri->b.y, (int)_tri->c.y));

    int16_t triWidth  = maxX-minX;
    int16_t triHeight = maxY-minY;

    //printf("ax: %d\tbx: %d\tcx: %d\n", (int)_tri->a.x, (int)_tri->b.x, (int)_tri->c.x);
    //printf("MaxX: %d. MinX: %d.\nMaxY: %d. MinY: %d\n", maxX, minX, maxY, minY);
    //printf("%s\t%s\n", (maxX > minX)?"True":"False", (maxY > minY)?"True":"False");
    //printf("Triangle Width: %d\nTriangleHeight: %d\n\n", triWidth, triHeight);

    if(!maxiterations || (triWidth < 1024 && triHeight < 512)){
        numPrims++;
        // Render and don't recur
        // Calculate the texture UV coords for the verts in this face.
        uint32_t uv0 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri->au), (uint32_t)((uint32_t)texture->v + _tri->av), texture->clut);
        uint32_t uv1 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri->bu), (uint32_t)((uint32_t)texture->v + _tri->bv), texture->page);
        uint32_t uv2 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri->cu), (uint32_t)((uint32_t)texture->v + _tri->cv), 0);

        // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
        dmaPtr = allocatePacket(activeChain, zIndex, 7);
        dmaPtr[0] = 0x808080 | gp0_shadedTriangle(false, true, false);
        dmaPtr[1] = gp0_xy(_tri->a.x, _tri->a.y);
        dmaPtr[2] = uv0;
        dmaPtr[3] = gp0_xy(_tri->b.x, _tri->b.y);
        dmaPtr[4] = uv1;
        dmaPtr[5] = gp0_xy(_tri->c.x, _tri->c.y);
        dmaPtr[6] = uv2;



        return;
    }

    // C is the oposite of the hypotenuse
    // therefore, A->B is the hypotenuse line.
    // Split take the mean average of these two points
    Vector2_16 newPoint;
    newPoint.x = (_tri->a.x + _tri->b.x) >> 1;
    newPoint.y = (_tri->a.y + _tri->b.y) >> 1;
    
    uint8_t newu = ((uint16_t)_tri->au + (uint16_t)_tri->bu) / 2;
    uint8_t newv = ((uint16_t)_tri->av + (uint16_t)_tri->bv) / 2;
    
    // c->a->n
    Tri2D triA;
    triA.a = _tri->c;
    triA.b = _tri->a;
    triA.c = newPoint;
    triA.au = _tri->cu;
    triA.av = _tri->cv;
    triA.bu = _tri->au;
    triA.bv = _tri->av;
    triA.cu = newu;
    triA.cv = newv;

    // b->c->n
    Tri2D triB;
    triB.a = _tri->b;
    triB.b = _tri->c;
    triB.c = newPoint;
    triB.au = _tri->bu;
    triB.av = _tri->bv;
    triB.bu = _tri->cu;
    triB.bv = _tri->cv;
    triB.cu = newu;
    triB.cv = newv;

    // Triangle A
    recursiveSubdivideAndRender(&triA, texture, zIndex, maxiterations-1);
    // Triangle B
    recursiveSubdivideAndRender(&triB, texture, zIndex, maxiterations-1);
}





// TODO: If texture NULL, render missing texture?
// Error check for missing model, etc
void model_renderTextured(Model *model, TextureInfo *texture, Camera *cam, uint16_t rotx, uint16_t roty, uint16_t rotz, int32_t tx, int32_t ty, int32_t tz){  
    
    // If distance is greater than 16 bits, simply don't render the object.
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
    

    for (int i = 0; i<model->numVerts; i+=3){
        // Load the next 3 verts into the gte
        gte_loadV0((GTEVector16 *) &model->verts[i]);
        if(i + 1 < model->numVerts){
            gte_loadV1((GTEVector16 *) &model->verts[i + 1]);
        }
        if(i + 2 < model->numVerts){
            gte_loadV2((GTEVector16 *) &model->verts[i + 2]);
        }
        // Transform
        gte_command(GTE_CMD_RTPT | GTE_SF);
        
        transformedVerts[i].XY = gte_getSXY0();
        transformedVerts[i].Z  = gte_getSZ0();
        if(i + 1 < model->numVerts){
            transformedVerts[i + 1].XY = gte_getSXY1();
            transformedVerts[i + 1].Z  = gte_getSZ1();
        }
        if(i + 2 < model->numVerts){
            transformedVerts[i + 2].XY = gte_getSXY2();
            transformedVerts[i + 2].Z  = gte_getSZ2();
        }
    }


    Tri2D _tri2d;
    // Add every triangle to the ordering table/dma chain for rendering.
    for(int i = 0; i<model->numTris; i++){
        // Load the GTE's internal registers
        gte_setSXY0((uint32_t) transformedVerts[model->tris[i].a].XY);
        gte_setSZ0(transformedVerts[model->tris[i].a].Z);
        
        gte_setSXY1((uint32_t) transformedVerts[model->tris[i].b].XY);
        gte_setSZ1(transformedVerts[model->tris[i].b].Z);
        
        gte_setSXY2((uint32_t) transformedVerts[model->tris[i].c].XY);
        gte_setSZ2(transformedVerts[model->tris[i].c].Z);

        //gte_loadV0((GTEVector16 *) &model->verts[model->tris[i].a]);
        //gte_loadV1((GTEVector16 *) &model->verts[model->tris[i].b]);
        //gte_loadV2((GTEVector16 *) &model->verts[model->tris[i].c]);
        //gte_command(GTE_CMD_RTPT | GTE_SF);

        gte_command(GTE_CMD_NCLIP);

        // If the face is facing away from us, don't bother rendering it.
        if(gte_getMAC0() <= 0){
            continue;
        }

        // Calculate the average Z value of all 3 verts.
        gte_command(GTE_CMD_AVSZ3 | GTE_SF);
        int zIndex = gte_getOTZ();

        // If too close/behind camera, don't render
        if(zIndex <= 3){
            continue;
        }
        
        // Don't render things too far away.
        if(zIndex >= ORDERING_TABLE_SIZE){
            continue;
        }
        
        if(false){
            uint32_t XY0 = gte_getSXY0();
            uint32_t XY1 = gte_getSXY1();
            uint32_t XY2 = gte_getSXY2();

            _tri2d.a.x = XY0 & 0xFFFF;
            _tri2d.b.x = XY1 & 0xFFFF;
            _tri2d.c.x = XY2 & 0xFFFF;
            _tri2d.a.y = XY0 >> 16;
            _tri2d.b.y = XY1 >> 16;
            _tri2d.c.y = XY2 >> 16;

            _tri2d.au = model->tris[i].au;
            _tri2d.av = model->tris[i].av;
            _tri2d.bu = model->tris[i].bu;
            _tri2d.bv = model->tris[i].bv;
            _tri2d.cu = model->tris[i].cu;
            _tri2d.cv = model->tris[i].cv;
        
            recursiveSubdivideAndRender(&_tri2d, texture, zIndex, 5);
        } else {
            // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
            dmaPtr = allocatePacket(activeChain, zIndex, 7);
            dmaPtr[0] = 0x808080 | gp0_shadedTriangle(false, true, false);
            dmaPtr[1] = gte_getSXY0();
            dmaPtr[2] = gp0_uv((uint32_t)((uint32_t)texture->u + model->tris[i].au), (uint32_t)((uint32_t)texture->v + model->tris[i].av) & 0x00FF, texture->clut);
            dmaPtr[3] = gte_getSXY1();
            dmaPtr[4] = gp0_uv((uint32_t)((uint32_t)texture->u + model->tris[i].bu), (uint32_t)((uint32_t)texture->v + model->tris[i].bv) & 0x00FF, texture->page);
            dmaPtr[5] = gte_getSXY2();
            dmaPtr[6] = gp0_uv((uint32_t)((uint32_t)texture->u + model->tris[i].cu), (uint32_t)((uint32_t)texture->v + model->tris[i].cv) & 0x00FF, 0);

            numPrims++;
        }
    }
    // Restore the translation and rotation back to the initial state as to not clobber any other models.
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

    if(_numVerts > maxNumVerts){
        maxNumVerts = _numVerts;
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