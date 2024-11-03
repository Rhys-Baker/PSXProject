#include "model.h"

#include "camera.h"
#include "cdrom.h"
#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>

int numPrims = 0;

typedef struct Vector2_16{
    int16_t x, y;
} Vector2_16;

typedef struct Tri3D{
    GTEVector16 a, b, c;
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
    
    // Add every triangle to the ordering table/dma chain for rendering.
    for(int i = 0; i<model->numTris; i++){
        Tri3D _tri;
        _tri.a.x = (model->verts[model->tris[i].a].x);
        _tri.a.y = (model->verts[model->tris[i].a].y);
        _tri.a.z = (model->verts[model->tris[i].a].z);

        _tri.b.x = (model->verts[model->tris[i].b].x);
        _tri.b.y = (model->verts[model->tris[i].b].y);
        _tri.b.z = (model->verts[model->tris[i].b].z);

        _tri.c.x = (model->verts[model->tris[i].c].x);
        _tri.c.y = (model->verts[model->tris[i].c].y);
        _tri.c.z = (model->verts[model->tris[i].c].z);

        _tri.au = model->tris[i].auv >> 8;
        _tri.av = model->tris[i].auv & 0xFF;
        _tri.bu = model->tris[i].buv >> 8;
        _tri.bv = model->tris[i].buv & 0xFF;
        _tri.cu = model->tris[i].cuv >> 8;
        _tri.cv = model->tris[i].cuv & 0xFF;

        // Load the GTE's internal registers
        gte_loadV0(&_tri.a);
        gte_loadV1(&_tri.b);
        gte_loadV2(&_tri.c);

        // Perform the transformation
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
        if(zIndex <= 1){
            continue;
        }
        
        // Don't render things too far away.
        if(zIndex >= ORDERING_TABLE_SIZE){
            continue;
        }

        uint32_t XY0 = gte_getSXY0();
        uint32_t XY1 = gte_getSXY1();
        uint32_t XY2 = gte_getSXY2();

        Tri2D _tri2d;

        
        _tri2d.a.x = XY0 & 0xFFFF;
        _tri2d.b.x = XY1 & 0xFFFF;
        _tri2d.c.x = XY2 & 0xFFFF;
        _tri2d.a.y = XY0 >> 16;
        _tri2d.b.y = XY1 >> 16;
        _tri2d.c.y = XY2 >> 16;
        
        _tri2d.au = _tri.au;
        _tri2d.av = _tri.av;
        _tri2d.bu = _tri.bu;
        _tri2d.bv = _tri.bv;
        _tri2d.cu = _tri.cu;
        _tri2d.cv = _tri.cv;



        // Oh boy, sure hope this doesn't cause a stack overflow :D
        recursiveSubdivideAndRender(&_tri2d, texture, zIndex, 5);

        // Calculate the texture UV coords for the verts in this face.
        //uint32_t uv0 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri.au), (uint32_t)((uint32_t)texture->v + _tri.av) & 0x00FF, texture->clut);
        //uint32_t uv1 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri.bu), (uint32_t)((uint32_t)texture->v + _tri.bv) & 0x00FF, texture->page);
        //uint32_t uv2 = gp0_uv((uint32_t)((uint32_t)texture->u + _tri.cu), (uint32_t)((uint32_t)texture->v + _tri.cv) & 0x00FF, 0);
        
        // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
        //dmaPtr = allocatePacket(activeChain, zIndex, 7);
        //dmaPtr[0] = 0x808080 | gp0_shadedTriangle(false, true, false);
        //dmaPtr[1] = gte_getSXY0();
        //dmaPtr[2] = uv0;
        //dmaPtr[3] = gte_getSXY1();
        //dmaPtr[4] = uv1;
        //dmaPtr[5] = gte_getSXY2();
        //dmaPtr[6] = uv2;

        // Render a triangle at the XY coords calculated via the GTE with the texture UVs calculated above
        //dmaPtr = allocatePacket(activeChain, zIndex, 6);
        //dmaPtr[0] = 0x0000FF | gp0_shadedTriangle(true, false, false);
        //dmaPtr[1] = gte_getSXY0();
        //dmaPtr[2] = 0x00FF00;
        //dmaPtr[3] = gte_getSXY1();
        //dmaPtr[4] = 0xFF0000;
        //dmaPtr[5] = gte_getSXY2();
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