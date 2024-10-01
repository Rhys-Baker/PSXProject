#include <assert.h>
#include <stdint.h>
#include "spu.h"
#include "registers.h"
#include "system.h"

/* Basic API */

static const int _DMA_CHUNK_SIZE = 4;
static const int _DMA_TIMEOUT    = 100000;
static const int _STATUS_TIMEOUT = 10000;

static bool _waitForStatus(uint16_t mask, uint16_t value){
    for(int timeout = _STATUS_TIMEOUT; timeout > 0; timeout -= 10) {
        if((SPU_STAT & mask) == value){
            return true;
        }

        delayMicroseconds(10);
    }

    return false;
}

void initSPU(void){
    BIU_DEV4_CTRL = 0
        | ( 1 <<  0) // Write delay
        | (14 <<  4) // Read delay
        | BIU_CTRL_RECOVERY
        | BIU_CTRL_WIDTH_16
        | BIU_CTRL_AUTO_INCR
        | ( 9 << 16) // Number of address lines
        | ( 0 << 24) // DMA read/write delay
        | BIU_CTRL_DMA_DELAY;
    
    SPU_CTRL = 0;
    _waitForStatus(0x3f, 0);

    SPU_MASTER_VOL_L = 0;
    SPU_MASTER_VOL_R = 0;
    SPU_REVERB_VOL_L = 0;
    SPU_REVERB_VOL_R = 0;
    SPU_REVERB_ADDR  = SPU_RAM_END / 8;

    SPU_FLAG_FM1     = 0;
    SPU_FLAG_FM2     = 0;
    SPU_FLAG_NOISE1  = 0;
    SPU_FLAG_NOISE2  = 0;
    SPU_FLAG_REVERB1 = 0;
    SPU_FLAG_REVERB2 = 0;

    SPU_CTRL = SPU_CTRL_ENABLE;
    _waitForStatus(0x3f, 0);

    // Place a dummy (silent) looping block at the beginning of SPU RAM.
    SPU_DMA_CTRL = 4;
    SPU_ADDR     = DUMMY_BLOCK_OFFSET / 8;

    SPU_DATA = 0x0500;
    for(int i = 7; i > 0; i--){
        SPU_DATA = 0;
    }

    SPU_CTRL = SPU_CTRL_XFER_WRITE | SPU_CTRL_ENABLE;
    _waitForStatus(SPU_CTRL_XFER_BITMASK | SPU_STAT_BUSY, SPU_CTRL_XFER_WRITE);
    delayMicroseconds(100);

    SPU_CTRL = SPU_CTRL_UNMUTE | SPU_CTRL_ENABLE;
    stopChannel(ALL_CHANNELS);
}

Channel getFreeChannel(void) {
    bool reenableInterrupts = disableInterrupts();

    for(Channel ch = 0; ch < NUM_CHANNELS; ch++){
        if(!SPU_CH_ADSR_VOL(ch)){
            if(reenableInterrupts){
                enableInterrupts();
            }
            return ch;
        }
    }
    if(reenableInterrupts){
        enableInterrupts();
    }
    return -1;
}

ChannelMask getFreeChannels(int count){
    bool reenableInterrupts = disableInterrupts();

    ChannelMask mask = 0;

    for(Channel ch = 0; ch < NUM_CHANNELS; ch++){
        if(SPU_CH_ADSR_VOL(ch)){
            continue;
        }

        mask |= 1 << ch;
        count--;

        if(!count){
            break;
        }
    }

    if(reenableInterrupts){
        enableInterrupts();
    }
    return mask;
}

void stopChannels(ChannelMask mask){
    mask &= ALL_CHANNELS;

    SPU_FLAG_OFF1 = mask & 0xffff;
    SPU_FLAG_OFF2 = mask >> 16;

    for(Channel ch = 0; mask; ch++, mask >>= 1){
        if(!(mask & 1)){
            continue;
        }

        SPU_CH_VOL_L(ch) = 0;
        SPU_CH_VOL_R(ch) = 0;
        SPU_CH_FREQ(ch)  = 1 << 12;
        SPU_CH_ADDR(ch)  = DUMMY_BLOCK_OFFSET / 8;
    }

    SPU_FLAG_ON1 = mask & 0xffff;
    SPU_FLAG_ON2 >> 16;
}

size_t upload(uint32_t offset, const void *data, size_t length, bool wait){
    length /= 4;
    
    // (Assert data is aligned uint32_t)

    length = (length + _DMA_CHUNK_SIZE - 1) / _DMA_CHUNK_SIZE;

    if(!waitForDMATransfer(DMA_SPU, _DMA_TIMEOUT)){
        return 0;
    }

    uint16_t ctrlReg = SPU_CTRL & ~SPU_CTRL_XFER_BITMASK;

    SPU_CTRL = ctrlReg;
    _waitForStatus(SPU_CTRL_XFER_BITMASK, 0);

    SPU_DMA_CTRL = 4;
    SPU_ADDR     = offset / 8;
    SPU_CTRL     = ctrlReg | SPU_CTRL_XFER_DMA_WRITE;
    _waitForStatus(SPU_CTRL_XFER_BITMASK, SPU_CTRL_XFER_DMA_WRITE);

    DMA_MADR(DMA_SPU) = (uint32_t)(data);
    DMA_BCR (DMA_SPU) = concat4_16(_DMA_CHUNK_SIZE, length);
    DMA_CHCR(DMA_SPU) = 0
        | DMA_CHCR_WRITE
        | DMA_CHCR_MODE_SLICE
        | DMA_CHCR_ENABLE;

    if(wait){
        waitForDMATransfer(DMA_SPU, _DMA_TIMEOUT);
    }

    return length * _DMA_CHUNK_SIZE * 4;
}

size_t download(uint32_t offset, void * data, size_t length, bool wait){
     length /= 4;
    
    // (Assert data is aligned uint32_t)

    length = (length + _DMA_CHUNK_SIZE - 1) / _DMA_CHUNK_SIZE;

    if(!waitForDMATransfer(DMA_SPU, _DMA_TIMEOUT)){
        return 0;
    }

    uint16_t ctrlReg = SPU_CTRL & ~SPU_CTRL_XFER_BITMASK;

    SPU_CTRL = ctrlReg;
    _waitForStatus(SPU_CTRL_XFER_BITMASK, 0);

    SPU_DMA_CTRL = 4;
    SPU_ADDR     = offset / 8;
    SPU_CTRL     = ctrlReg | SPU_CTRL_XFER_DMA_READ;
    _waitForStatus(SPU_CTRL_XFER_BITMASK, SPU_CTRL_XFER_DMA_READ);

    DMA_MADR(DMA_SPU) = (uint32_t)(data);
    DMA_BCR (DMA_SPU) = concat4_16(_DMA_CHUNK_SIZE, length);
    DMA_CHCR(DMA_SPU) = 0
        | DMA_CHCR_READ
        | DMA_CHCR_MODE_SLICE
        | DMA_CHCR_ENABLE;
    
    if(wait){
        waitForDMATransfer(DMA_SPU, _DMA_TIMEOUT);
    }

    return length * _DMA_CHUNK_SIZE * 4;
}

/* Sound Class */
void sound_create(Sound *sound){
    sound->offset     = 0;
    sound->sampleRate = 0;
    sound->length     = 0;
}
bool sound_initFromVAGHeader(Sound *sound, VAGHeader *vagHeader, uint32_t _offset){
    if(!vagHeader_validateMagic(vagHeader)){
        return false;
    }
    sound->offset     = _offset;
    sound->sampleRate = vagHeader_getSPUSampleRate(vagHeader);
    sound->length     = vagHeader_getSPULength(vagHeader);
    return true;
}

Channel sound_playOnChannel(Sound *sound, uint16_t left, uint16_t right, Channel ch) {
    if((ch<0) || (ch >= NUM_CHANNELS)){
        return -1;
    }
    if(!sound->offset){
        return -1;
    }
    SPU_CH_VOL_L(ch) = left;
	SPU_CH_VOL_R(ch) = right;
	SPU_CH_FREQ (ch) = sound->sampleRate;
	SPU_CH_ADDR (ch) = sound->offset / 8;
	SPU_CH_ADSR1(ch) = 0x00ff;
	SPU_CH_ADSR2(ch) = 0x0000;
    
    if(ch < 16){
        SPU_FLAG_ON1 = 1 << ch;
    } else {
        SPU_FLAG_ON2 = 1 << (ch - 16);
    }

    return ch;
}

/* Stream Class */

/*
 * The stream driver lays out a ring buffer of interleaved audio chunks in SPU
 * RAM as follows:
 *
 * +---------------------------------+---------------------------------+-----
 * |              Chunk              |              Chunk              |
 * | +------------+------------+     | +------------+------------+     |
 * | |  Ch0 data  |  Ch1 data  | ... | |  Ch0 data  |  Ch1 data  | ... | ...
 * | +------------+------------+     | +------------+------------+     |
 * +-^------------^------------------+-^------------^------------------+-----
 *   | Ch0 start  | Ch1 start          | Ch0 loop   | Ch1 loop
 *                                     | IRQ address
 *
 * The length of each chunk is given by the interleave size multiplied by the
 * channel count. Each data block must be terminated with the loop end and
 * sustain flags set in order to make the channels "jump" to the next chunk's
 * blocks.
 * - SpicyJpeg
 */

void stream_configureIRQ(Stream *stream){
    uint16_t ctrlReg = SPU_CTRL;

    // Disable the IRQ if an underrun occurs.
    // TODO: handle this in a slightly better way
    if(!stream->_bufferedChunks){
        SPU_CTRL = ctrlReg & ~SPU_CTRL_IRQ_ENABLE;
        return;
    }

    // Exit if the IRQ has been set up before and not yet acknowledged by
    // handleInterrupt().
    if(ctrlReg & SPU_CTRL_IRQ_ENABLE){
        return;
    }

    ChannelMask tempMask = stream->_channelMask;
    uint32_t chunkOffset = stream_getChunkOffset(stream, stream->_head);

    SPU_IRQ_ADDR = chunkOffset / 8;
    SPU_CTRL     = ctrlReg | SPU_CTRL_IRQ_ENABLE;

    for(Channel ch = 0; tempMask; ch++, tempMask >>= 1){
        if(!(tempMask & 1)){
            continue;
        }

        SPU_CH_LOOP_ADDR(ch) = chunkOffset /8;
        chunkOffset         += stream->interleave;
    }
}

void stream_create(Stream *stream){
    stream->_channelMask = 0;
    stream->offset       = 0;
    stream->interleave   = 0;
    stream->numChunks    = 0;
    stream->sampleRate   = 0;
    stream->channels     = 0;

    stream_resetBuffer(&stream);
}

bool stream_initFromVAGHeader(Stream *stream, const VAGHeader *vagHeader, uint32_t _offset, size_t _numChunks){
    if(stream_isPlaying(stream)){
        return false;
    }
    if(!vagHeader_validateInterleavedMagic(vagHeader)){
        return false;
    }

    stream_resetBuffer(stream);

    stream->offset     = _offset;
    stream->interleave = vagHeader->interleave;
    stream->numChunks  = _numChunks;
    stream->sampleRate = vagHeader_getSPUSampleRate(vagHeader);
    stream->channels   = vagHeader_getNumChannels(vagHeader);
    return true;
}
 
ChannelMask stream_startWithChannelMask(Stream *stream, uint16_t left, uint16_t right, ChannelMask mask) {
    if(stream_isPlaying(stream) || !stream->_bufferedChunks){
        return 0;
    }

    mask &= ALL_CHANNELS;

    ChannelMask tempMask = mask;
    uint32_t chunkOffset = stream_getChunkOffset(stream, stream->_head);
    int isRightCh        = 0;

    for(Channel ch = 0; tempMask; ch++, tempMask >>= 1){
        if(!(tempMask & 1)){
            continue;
        }
    
        // Assume each pair of channels is a stero pair. If the channel count is odd,
        // assume the last channel is mono.

        if(isRightCh) {
            SPU_CH_VOL_L(ch) = 0;
            SPU_CH_VOL_R(ch) = right;
        } else if(tempMask != 1){
            SPU_CH_VOL_L(ch) = left;
            SPU_CH_VOL_R(ch) = 0;
        } else {
            SPU_CH_VOL_L(ch) = left;
            SPU_CH_VOL_R(ch) = right;
        }

        SPU_CH_FREQ(ch)  = stream->sampleRate;
        SPU_CH_ADDR(ch)  = chunkOffset / 8;
        SPU_CH_ADSR1(ch) = 0x00ff;
        SPU_CH_ADSR2(ch) = 0x0000;

        chunkOffset += stream->interleave;
        isRightCh   ^= 1;
    }

    stream->_channelMask = mask;
    SPU_FLAG_ON1 = mask & 0xffff;
    SPU_FLAG_ON2 = mask >> 16;

    stream_handleInterrupt(stream);
    return mask;
}

void stream_stop(Stream *stream){
    if(!stream_isPlaying(stream)){
        return;
    }

    // Disabling the IRQ is always required in order to acknowledge it.
    SPU_CTRL &= ~SPU_CTRL_IRQ_ENABLE;

    stream->_head = (stream->_head + 1) % stream->numChunks;
    stream->_bufferedChunks--;
    stream_configureIRQ(stream);
}

size_t stream_feed(Stream *stream, const void *data, size_t length){
    bool reenableInterrupts = disableInterrupts();

    uintptr_t ptr = (uintptr_t)(data);
    size_t chunkLength = stream_getChunkLength(stream);

    length = min(length, stream_getFreeChunkCount(stream) * chunkLength);

    for(int i = length; i >= (int)(chunkLength); i -= chunkLength){
        upload(
            stream_getChunkOffset(stream, stream->_tail), (const void *)(ptr),
            chunkLength, true
        );

        ptr += chunkLength;
        stream->_tail = (stream->_tail + 1) % stream->numChunks;
        stream->_bufferedChunks++;
    }

    if(stream_isPlaying(stream)){
        stream_configureIRQ(stream);
    }

    flushWriteQueue();
    if(reenableInterrupts){
        enableInterrupts();
    }
    return length;
}

void stream_resetBuffer(Stream *stream){
    stream->_head            = 0;
    stream->_tail            = 0;
    stream->_bufferedChunks  = 0;
}