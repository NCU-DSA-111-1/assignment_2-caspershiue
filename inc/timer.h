#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <ev.h>

extern ev_io stop_watcher; 
extern ev_timer timeout_watcher;
extern time_t xtimestart,xtime,ytimestart,ytime,xusedtime,yusedtime;
extern int xhour, xminute, xsecond,yhour, yminute, ysecond;

void timer();
void timeout_cb (EV_P_ ev_timer *w, int revents);
void stop_cb (EV_P_ ev_io *w, int revents);

#endif