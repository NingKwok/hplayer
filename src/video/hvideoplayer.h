#ifndef HVIDEOPLAYER_H
#define HVIDEOPLAYER_H

#include "hmedia.h"
#include "hw/hframe.h"
#include "hw/hstring.h"
#include "hw/hlog.h"

#define DEFAULT_FPS         25
#define DEFAULT_FRAME_CACHE 5

#define SIGNAL_END_OF_FILE  0x01

inline string strtime(int64 ms) {
    int sec = ms / 1000;

    int min = sec / 60;
    sec = sec % 60;

    int hour = min / 60;
    min = min % 60;

    return asprintf("%02d:%02d:%02d", hour, min, sec);
}

class HVideoPlayer
{
public:
    HVideoPlayer(){
        set_frame_cache(DEFAULT_FRAME_CACHE);
        fps = DEFAULT_FPS;
        duration = 0;
        start_time = 0;
        signal = 0;
    }
    virtual ~HVideoPlayer() {}

    virtual int start() = 0;
    virtual int stop() = 0;
    virtual int pause() = 0;
    virtual int resume() = 0;

    virtual int seek(int64 ms) {
        return 0;
    }

    void set_media(HMedia& media){
        this->media = media;
    }

    FrameStats get_frame_stats(){
        return frame_buf.frame_stats;
    }

    FrameInfo get_frame_info(){
        return frame_buf.frame_info;
    }

    void set_frame_cache(int cache){
        frame_buf.setCache(cache);
    }

    int push_frame(HFrame* pFrame){
        return frame_buf.push(pFrame);
    }

    int pop_frame(HFrame* pFrame){
        return frame_buf.pop(pFrame);
    }

public:
    HMedia      media;
    int         fps;
    int64       duration; // ms
    int64       start_time; // ms
    int         signal;
protected:
    HFrameBuf   frame_buf;
};

#endif // HVIDEOPLAYER_H
