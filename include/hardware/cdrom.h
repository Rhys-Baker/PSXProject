#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern void  *cdromReadDataPtr;
extern size_t cdromReadDataSectorSize;
extern size_t cdromReadDataNumSectors;

extern uint8_t cdromResponse[16];
extern uint8_t cdromRespLength;
extern uint8_t cdromStatus;

typedef enum {
    IRQ_NONE              = 0,
    IRQ_DATA_READY        = 1,
    IRQ_BLOCKING_CMD_DONE = 2,
    IRQ_CMD_ACKNOWLEDGE   = 3,
    IRQ_TRACK_END         = 4,
    IRQ_ERROR             = 5
} CDROMIRQType;

typedef enum {
    MODE_CDDA               = 1 << 0,
    MODE_PAUSE_AT_TRACK_END = 1 << 1,
    MODE_CDDA_REPORT        = 1 << 2,
    MODE_XA_SECTOR_FILTER   = 1 << 3,
    MODE_IGNORE_PREV        = 1 << 4,
    MODE_SECTOR_SIZE_2340   = 1 << 5,
    MODE_XA_ADPCM           = 1 << 6,
    MODE_2X_SPEED           = 1 << 7
} CDROMMode;

typedef enum {
	CDROM_NOP           = 0x01,	// Updates the current CD-ROM status and resets the CdlStatShellOpen flag, without doing anything else.
	CDROM_SETLOC        = 0x02,	// Sets the seek target location, but does not seek. Actual seeking begins upon issuing a seek or read command.
	CDROM_PLAY			= 0x03,	// Begins CD-DA playback. Parameter specifies an optional track number to play (some emulators do not support it).
	CDROM_FORWARD		= 0x04,	// Starts fast-forwarding (CD-DA only). Issue CdlPlay to stop fast-forwarding.
	CDROM_BACKWARD		= 0x05,	// Starts rewinding (CD-DA only). Issue CdlPlay to stop rewinding.
	CDROM_READN         = 0x06,	// Begins reading data sectors and/or playing XA-ADPCM with automatic retry. Used in conjunction with CdReadyCallback().
	CDROM_STANDBY       = 0x07,	// Starts the spindle motor if it was previously stopped.
	CDROM_STOP          = 0x08,	// Stops playback or data reading and shuts down the spindle motor.
	CDROM_PAUSE		    = 0x09,	// Stops playback or data reading without stopping the spindle motor.
	CDROM_INIT			= 0x0a,	// Initializes the CD-ROM controller and aborts any ongoing command.
	CDROM_MUTE			= 0x0b,	// Mutes the drive's audio output (both CD-DA and XA-ADPCM).
	CDROM_DEMUTE		= 0x0c,	// Unmutes the drive's audio output (both CD-DA and XA-ADPCM).
	CDROM_SETFILTER	    = 0x0d,	// Configures the XA-ADPCM sector filter.
	CDROM_SETMODE		= 0x0e,	// Sets the CD-ROM mode flags (see CdlModeFlags).
	CDROM_GETPARAM		= 0x0f,	// Returns the current CD-ROM mode flags and XA-ADPCM filter settings.
	CDROM_GETLOCL		= 0x10,	// Returns the location, mode and XA subheader of the current data sector. Does not work on CD-DA sectors.
	CDROM_GETLOCP		= 0x11,	// Returns the current physical CD location (using subchannel Q data).
	CDROM_SETSESSION	= 0x12,	// Attempts to seek to the specified session on a multi-session disc. Used by CdLoadSession().
	CDROM_GETTN		    = 0x13,	// Returns the total number of tracks on the disc.
	CDROM_GETTD		    = 0x14,	// Returns the starting location of the specified track number.
	CDROM_SEEKL		    = 0x15,	// Seeks (using data sector headers) to the position set by the last CdlSetloc command. Does not work on CD-DA sectors.
	CDROM_SEEKP		    = 0x16,	// Seeks (using subchannel Q data) to the position set by the last CdlSetloc command.
	CDROM_TEST			= 0x19,	// Executes a test subcommand. Shall be issued using CdCommand() rather than CdControl().
	CDROM_GETID		    = 0x1a,	// Identifies the disc type and returns its license string if any.
	CDROM_READS		    = 0x1b,	// Begins reading data sectors and/or playing XA-ADPCM in real-time (without automatic retry) mode.
	CDROM_RESET		    = 0x1c,	// Resets the CD-ROM controller (similar behavior to manually opening and closing the lid).
	CDROM_GETQ			= 0x1d,	// Reads up to 10 raw bytes of subchannel Q data directly from the disc's table of contents.
	CDROM_READTOC		= 0x1e	// Forces reading of the disc's table of contents.
} CDROMCommand;

typedef enum {
	CDROM_STAT_ERROR        = 1 << 0,	// A command error has occurred. Set when an invalid command or parameters are sent.
	CDROM_STAT_STANDBY      = 1 << 1,	// Set whenever the spindle motor is powered on or spinning up.
	CDROM_STAT_SEEKERROR    = 1 << 2,	// A seek error has occurred.
	CDROM_STAT_IDERROR      = 1 << 3,	// Disc has been rejected due to being unlicensed (on consoles without a modchip installed).
	CDROM_STAT_SHELLOPEN    = 1 << 4,	// Lid is open or has been opened before. This flag is cleared by sending a CdlNop command.
	CDROM_STAT_READ         = 1 << 5,	// Drive is currently reading data and/or playing XA-ADPCM.
	CDROM_STAT_SEEK         = 1 << 6,	// Drive is currently seeking.
	CDROM_STAT_PLAY         = 1 << 7	   // Drive is currently playing a CD-DA track.
} CDROM_STAT;

typedef struct {
    uint8_t minute, second, frame;
} MSF;

#define toBCD(i) (((i) / 10 * 16) | ((i) % 10))
#define CDROM_COMMAND_ADDRESS 0x1F801801

#define CDROM_BUSY (CDROM_HSTS & CDROM_HSTS_BUSYSTS)


void initCDROM(void);

void issueCDROMCommand(uint8_t cmd, const uint8_t *arg, size_t argLength);

void waitForINT3();

void convertLBAToMSF(MSF *msf, uint32_t lba);

void startCDROMRead(uint32_t lba, void *ptr, size_t numSectors, size_t sectorSize, bool doubleSpeed);

bool readDiscName(char *output);

void cdromINT1(void);
void cdromINT2(void);
void cdromINT3(void);
void cdromINT4(void);
void cdromINT5(void);
