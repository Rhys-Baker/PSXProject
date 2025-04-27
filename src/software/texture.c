#include "texture.h"

#include "cdrom.h"
#include "filesystem.h"
#include "gpu.h"
#include <stdlib.h>

#include <stdio.h>



// Load texture from disc
size_t texture_loadTIM(char *name, TextureInfo *texinfo){
    uint32_t textureLba;

    uint32_t fileSize[2];
    uint8_t *fileBuffer;
    uint32_t fileOffset = 0;
    uint32_t numSectors;

    uint8_t *clut_data;
    uint32_t clut_size = 0;
    uint16_t clut_u = 0;
    uint16_t clut_v = 0;
    uint16_t clut_w = 0;
    uint16_t clut_h = 0;

    uint8_t *texture_data;
    uint32_t texture_size = 0;
    uint16_t texture_u = 0;
    uint16_t texture_v = 0;
    uint16_t texture_w = 0;
    uint16_t texture_h = 0;

    
    //uint8_t sectorBuffer[1024];
    

    textureLba = getLbaToFile(name, fileSize);
    if(!textureLba){
        return 1; // Texture not found. TODO: Replace with better error handling
    }

    // Allocate a file buffer
    numSectors = (fileSize[1] / 2048) + 1;
    fileBuffer = malloc(numSectors * 2048);

    // Read the file into the file buffer
    startCDROMRead(
        textureLba, fileBuffer,
        numSectors,
        2048,
        true,
        true
    );

    printf("Start file: %d\n", fileOffset);
    // Begin parsing the header
    uint8_t fileId = fileBuffer[fileOffset++];
    if(fileId != 0x10){
        free(fileBuffer);
        return 2; // Invalid header
    }

    uint8_t version = fileBuffer[fileOffset++];
    if(version != 0x00){
        free(fileBuffer);
        return 3; // Invalid version
    }

    fileOffset += 2; // Skip the reserved
    
    struct flags {
        unsigned int type : 3;
        unsigned int hasClut : 1;
        unsigned int reserved : 28;
    } flags;
    
    uint32_t rawFlags = 
        ((uint32_t)fileBuffer[fileOffset ++]      ) |
        ((uint32_t)fileBuffer[fileOffset ++] <<  8) |
        ((uint32_t)fileBuffer[fileOffset ++] << 16) |
        ((uint32_t)fileBuffer[fileOffset ++] << 24);
    printf("Flags: 0x%08x\n", rawFlags);

    flags.type =  rawFlags & 0x7;
    flags.hasClut = (rawFlags >> 3) & 0x1;
    flags.reserved = (rawFlags >> 4);

    printf("End of header: %d\n", fileOffset);
    
    if(flags.type > 3){
        free(fileBuffer);
        return 4; // Invalid type
    }

    if(flags.hasClut){
        printf("Start of CLUT: %d\n", fileOffset);
        printf("0x%8x\n0x%8x\n0x%8x\n",
            (
                (uint32_t)(fileBuffer[fileOffset+0] << 24)|
                (uint32_t)(fileBuffer[fileOffset+1] << 16)|
                (uint32_t)(fileBuffer[fileOffset+2] <<  8)|
                (uint32_t)(fileBuffer[fileOffset+3])
            ),
            (
                (uint32_t)(fileBuffer[fileOffset+4] << 24)|
                (uint32_t)(fileBuffer[fileOffset+5] << 16)|
                (uint32_t)(fileBuffer[fileOffset+6] <<  8)|
                (uint32_t)(fileBuffer[fileOffset+7])
            ),
            (
                (uint32_t)(fileBuffer[fileOffset+ 8] << 24)|
                (uint32_t)(fileBuffer[fileOffset+ 9] << 16)|
                (uint32_t)(fileBuffer[fileOffset+10] <<  8)|
                (uint32_t)(fileBuffer[fileOffset+11])
            )
        );
        // CLUT data section
        clut_size = (
            (uint32_t)(fileBuffer[fileOffset ++]      )|
            (uint32_t)(fileBuffer[fileOffset ++] <<  8)|
            (uint32_t)(fileBuffer[fileOffset ++] << 16)|
            (uint32_t)(fileBuffer[fileOffset ++] << 24)
        );
        
        clut_u = (
            (uint16_t)(fileBuffer[fileOffset ++]      )|
            (uint16_t)(fileBuffer[fileOffset ++] <<  8)
        );
        clut_v = (
            (uint16_t)(fileBuffer[fileOffset ++]      )|
            (uint16_t)(fileBuffer[fileOffset ++] <<  8)
        );
        clut_w = (
            (uint16_t)(fileBuffer[fileOffset ++]      )|
            (uint16_t)(fileBuffer[fileOffset ++] <<  8)
        );
        clut_h = (
            (uint16_t)(fileBuffer[fileOffset ++]      )|
            (uint16_t)(fileBuffer[fileOffset ++] <<  8)
        );
        
        clut_data = &fileBuffer[fileOffset];
        fileOffset+=clut_size-0x0c;
    }
    

    printf("Start of texture: %d\n", fileOffset);
    printf("0x%8x\n0x%8x\n0x%8x\n",
        (
            (uint32_t)(fileBuffer[fileOffset+0] << 24)|
            (uint32_t)(fileBuffer[fileOffset+1] << 16)|
            (uint32_t)(fileBuffer[fileOffset+2] <<  8)|
            (uint32_t)(fileBuffer[fileOffset+3])
        ),
        (
            (uint32_t)(fileBuffer[fileOffset+4] << 24)|
            (uint32_t)(fileBuffer[fileOffset+5] << 16)|
            (uint32_t)(fileBuffer[fileOffset+6] <<  8)|
            (uint32_t)(fileBuffer[fileOffset+7])
        ),
        (
            (uint32_t)(fileBuffer[fileOffset+ 8] << 24)|
            (uint32_t)(fileBuffer[fileOffset+ 9] << 16)|
            (uint32_t)(fileBuffer[fileOffset+10] <<  8)|
            (uint32_t)(fileBuffer[fileOffset+11])
        )
    );
    // Pixel data section
    texture_size = (
        (uint32_t)(fileBuffer[fileOffset ++]      )|
        (uint32_t)(fileBuffer[fileOffset ++] <<  8)|
        (uint32_t)(fileBuffer[fileOffset ++] << 16)|
        (uint32_t)(fileBuffer[fileOffset ++] << 24)
    );
    texture_u = (
        (uint16_t)(fileBuffer[fileOffset ++]      )|
        (uint16_t)(fileBuffer[fileOffset ++] <<  8)
    );
    texture_v = (
        (uint16_t)(fileBuffer[fileOffset ++]      )|
        (uint16_t)(fileBuffer[fileOffset ++] <<  8)
    );
    texture_w = (
        (uint16_t)(fileBuffer[fileOffset ++]      )|
        (uint16_t)(fileBuffer[fileOffset ++] <<  8)
    );
    texture_h = (
        (uint16_t)(fileBuffer[fileOffset ++]      )|
        (uint16_t)(fileBuffer[fileOffset ++] <<  8)
    );

    texture_data = &fileBuffer[fileOffset];
    
    printf(" Texture Info\n");
    printf(" ->Size: %d\n", texture_size);
    printf(" ->flags.type: %d\n", flags.type);
    printf(" ->flags.hasClut: %s\n", flags.hasClut ? "Yes" : "No");
    printf(" ->flags.reserved: %d\n", flags.reserved);
    printf(" ->X: %d; Y: %d\n", texture_u, texture_v);
    printf(" ->W: %d; H: %d\n", texture_w, texture_h);

    if(flags.hasClut){
        // Upload the texture into VRAM and wait.
        sendVRAMData(texture_data, texture_u, texture_v, texture_w, texture_h);
        waitForDMADone();
        sendVRAMData(clut_data, clut_u, clut_v, clut_w, clut_h);
        waitForDMADone();
    } else {
        uploadTexture(
            texinfo, texture_data, texture_u, texture_v, texture_w, texture_h
        );
    }


    // Upload texture to VRAM
    free(fileBuffer);
    return 0;
}
