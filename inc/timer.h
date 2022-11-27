#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <ev.h>

extern ev_io stop_watcher; 
extern ev_timer timeout_watcher;
extern time_t xtimestart,xtime,ytimestart,ytime,xusedtime,yusedtime;
extern int xhour, xminute, xsecond,yhour, yminute, ysecond;

void timer();
void timerm();
void timerh1();
void timerh2();
void timerp();
void timeout_cb (EV_P_ ev_timer *w, int revents);
void timeout_cbm (EV_P_ ev_timer *w, int revents);
void timeout_cbh1 (EV_P_ ev_timer *w, int revents);
void timeout_cbh2 (EV_P_ ev_timer *w, int revents);
void timeout_cbp (EV_P_ ev_timer *w, int revents);
void stop_cb (EV_P_ ev_io *w, int revents);

#endif