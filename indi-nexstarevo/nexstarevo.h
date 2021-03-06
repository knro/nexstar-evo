#ifndef NEXSTAREVO_H
#define NEXSTAREVO_H

#include "libindi/indiguiderinterface.h"
#include "libindi/inditelescope.h"
#include "libindi/alignment/AlignmentSubsystemForDrivers.h"
#include "NexStarAUXScope.h"


class NexStarEvo : public INDI::Telescope, public INDI::AlignmentSubsystem::AlignmentSubsystemForDrivers
{
public:
    NexStarEvo();

protected:
    virtual bool Abort();
    bool canSync();
    virtual bool Connect();
    virtual bool Disconnect();
    virtual const char *getDefaultName();
    bool Goto(double ra,double dec);
    virtual bool initProperties();
    friend void ISNewBLOB (const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n);
    virtual bool ISNewBLOB (const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n);
    friend void ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
    virtual bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
    friend void ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);
    virtual bool ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);
    friend void ISNewText (const char *dev, const char *name, char *texts[], char *names[], int n);
    virtual bool ISNewText (const char *dev, const char *name, char *texts[], char *names[], int n);
    // TODO: Switch to AltAz from N-S/W-E
    virtual bool MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command);
    virtual bool MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command);
    virtual bool ReadScopeStatus();
    bool Sync(double ra, double dec);
    virtual void TimerHit();
    virtual bool updateLocation(double latitude, double longitude, double elevation);

private:
    static const long STEPS_PER_REVOLUTION;
    static const double STEPS_PER_DEGREE;
    static const double DEFAULT_SLEW_RATE;
    static const double TRACK_SCALE;
    static const long MAX_ALT;
    static const long MIN_ALT;

    NexStarAUXScope scope;

    enum AxisStatus { STOPPED, SLEWING, SLEWING_TO };
    enum AxisDirection { FORWARD, REVERSE };

    AxisStatus AxisStatusALT;
    AxisDirection AxisDirectionALT;
    double AxisSlewRateALT;
    long CurrentALT;
    long GotoTargetALT;

    AxisStatus AxisStatusAZ;
    AxisDirection AxisDirectionAZ;
    double AxisSlewRateAZ;
    long CurrentAZ;
    long GotoTargetAZ;

    // Previous motion direction
    // TODO: Switch to AltAz from N-S/W-E
    typedef enum { PREVIOUS_NS_MOTION_NORTH = DIRECTION_NORTH,
                    PREVIOUS_NS_MOTION_SOUTH = DIRECTION_SOUTH,
                    PREVIOUS_NS_MOTION_UNKNOWN = -1} PreviousNSMotion_t;
    PreviousNSMotion_t PreviousNSMotion;
    typedef enum { PREVIOUS_WE_MOTION_WEST = DIRECTION_WEST,
                    PREVIOUS_WE_MOTION_EAST = DIRECTION_EAST,
                    PREVIOUS_WE_MOTION_UNKNOWN = -1} PreviousWEMotion_t;
    PreviousWEMotion_t PreviousWEMotion;

    // Tracking
    ln_equ_posn CurrentTrackingTarget;
    long OldTrackingTarget[2];

    // Tracing in timer tick
    int TraceThisTickCount;
    bool TraceThisTick;

    unsigned int DBG_NSEVO;
};

#endif // NEXSTAREVO_H
