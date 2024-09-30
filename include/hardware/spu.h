// Adapted by Rhys Baker
// Based on the C++ code at https://github.com/spicyjpeg/573in1/blob/dev/src/common/spu.hpp

#pragma once

#include <stddef.h>
#include <stdint.h>
#include "registers.h"


#define Channel int
#define ChannelMask uint32_t

enum LoopFlag {
    LOOP_END     = 1 << 0,
    LOOP_SUSTAIN = 1 << 1,
    LOOP_START   = 1 << 2
};

static const uint32_t DUMMY_BLOCK_OFFSET = 0x01000;
static const uint32_t DUMMY_BLOCK_END    = 0x01010;
static const uint32_t SPU_RAM_END        = 0x7fff0;

static const int      NUM_CHANNELS = 24;
static const uint16_t MAX_VOLUME   = 0x3fff;

static const ChannelMask ALL_CHANNELS = (1 << NUM_CHANNELS) - 1;

/* Utilities */

static inline uint32_t concat4(uint8_t a, uint8_t b, uint8_t c, uint8_t d){
    return (a | (b << 8) | (c << 16) | (d << 24));
}

static inline int min(int a, int b){
    return (a<b) ? a : b;
}

/* Basic SPU API */

void initSPU(void);
Channel getFreeChannel(void);
ChannelMask getFreeChannels(int count);
void stopChannels(ChannelMask mask);

static inline void setMasterVolume(uint16_t master, uint16_t reverb){
    SPU_MASTER_VOL_L = master;
    SPU_MASTER_VOL_R = master;
    SPU_REVERB_VOL_L = reverb;
    SPU_REVERB_VOL_R = reverb;
}

static inline void stopChannel(Channel ch){
    stopChannels(1 << ch);
}

size_t upload(uint32_t offset, const void *data, size_t length, bool wait);
size_t download(uint32_t offset, void *data, size_t length, bool wait);


/* VAGHeader Class */

static const size_t INTERLEAVED_VAG_BODY_OFFSET = 2048;


typedef struct VAGHeader{
    uint32_t magic, version, interleave, length, sampleRate;
    uint16_t _reserved[5], channels;
    char     name[16];
} VAGHeader;

inline bool vagHeader_validateMagic(VAGHeader *vagHeader){
    return (vagHeader->magic == concat4('V', 'A', 'G', 'p')) && (vagHeader->channels <= 1);
}

inline bool vagHeader_validateInterleavedMagic(VAGHeader *vagHeader){
    return (vagHeader->magic == concat4('V', 'A', 'G', 'i')) && vagHeader->interleave;
}

inline uint16_t vagHeader_getSPUSampleRate(VAGHeader *vagHeader){
    return(__builtin_bswap32(vagHeader->sampleRate) << 12) / 44100;
}

inline uint16_t vagHeader_getSPUSampleRate(VAGHeader *vagHeader){
    return __builtin_bswap32(vagHeader->length) /8;
}

inline int getNumChannels(VAGHeader *vagHeader){
    return vagHeader->channels ? vagHeader->channels : 2;
}

inline const void *getData(VAGHeader *vagHeader){
    return vagHeader + 1;
}


/* Sound Class */

typedef struct Sound {
    uint32_t offset;
    uint16_t sampleRate, length;
} Sound;

bool sound_initFromVAGHeader(Sound *sound, const VAGHeader *vagHeader, uint32_t _offset);
Channel sound_playOnChannel(Sound *sound, uint16_t left, uint16_t right, Channel ch);

inline Channel sound_play(Sound *sound, uint16_t left, uint16_t right){
    return sound_playOnChannel(sound, left, right, getFreeChannel());
}


/* Stream Class */

typedef struct Stream{
    uint32_t _channelMask;
    uint16_t _head, _tail, _bufferedChunks;

    uint32_t offset;
    uint16_t interleave, numChunks, sampleRate, channels;
} Stream;

inline uint32_t stream_getChunkOffset(Stream *stream, size_t chunk) {
    return stream->offset + stream_getChunkLnegth(stream) * chunk;
}
void stream_configureIRQ(Stream stream);

// Destructor here if needed

inline ChannelMask stream_start(Stream *stream, uint16_t left, uint16_t right){
    return stream_startWithChannelMask(stream, left, right, getFreeChannels(NUM_CHANNELS));
}
inline bool stream_isPlaying(Stream *stream){
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    return (stream->_channelMask != 0);
}
inline bool stream_isUnderrun(Stream *stream){
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    return !stream->_bufferedChunks;
}

inline size_t stream_getChunkLength(Stream *stream) {
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // The currently playing chunk cannot be overwritten.
    size_t playingChunk = stream->_channelMask ? 1 : 0;
    return stream->numChunks - (stream->_bufferedChunks + playingChunk);
}

Stream *stream_create(void);
bool stream_initFromVAGHeader(Stream *stream, const VAGHeader *vagHeader, uint32_t _offset, size_t _numChunks);
ChannelMask stream_startWithChannelMask(Stream *stream, uint16_t left, uint16_t right, ChannelMask mask);
void stream_stop(Stream *stream);
void stream_handleInterrupt(Stream *stream);

size_t stream_feed(Stream *stream, const void *data, size_t length);
void stream_resetBuffer(Stream *stream);
