#include "../inc/timer.h"
#include "../inc/shogi.h"

ev_io stop_watcher; 
ev_timer timeout_watcher;
time_t xtimestart,xtime,ytimestart,ytime,xusedtime,yusedtime;
int xhour, xminute, xsecond,yhour, yminute, ysecond;

void timer()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, stop_cb,0, EV_READ);
    ev_io_start (loop, &stop_watcher);
    ev_timer_init(&timeout_watcher, timeout_cb,0,1);
    ev_timer_start (loop, &timeout_watcher);
    if(player==1)
        xtimestart=time(NULL);
    else
        ytimestart=time(NULL);
    ev_run(loop,0);
}
void timeout_cb (EV_P_ ev_timer *w, int revents)
{
    if(player==1){
        xtime = time(NULL);
        xhour = (xtime - xtimestart + xusedtime) / 3600;
        xminute = (xtime - xtimestart + xusedtime - xhour * 3600)/60;
        xsecond = xtime - xtimestart + xusedtime - xhour * 3600 - xminute * 60;
        system("clear");
        printf(" 玩家x遊戲時間：%02d:%02d:%02d\n",xhour,xminute,xsecond);
        printf(" 玩家y遊戲時間：%02d:%02d:%02d\n\n",yhour,yminute,ysecond);
        chessprint();
        printf(" 打入棋子請輸入H\n 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
        printf(" 玩家X輸入移動棋子的 X 座標與 Y 座標: ");
        fflush(stdout);
    }
    else{
        ytime = time(NULL);
        yhour = (ytime - ytimestart + yusedtime) / 3600;
        yminute = (ytime - ytimestart + yusedtime - yhour * 3600)/60;
        ysecond = ytime - ytimestart + yusedtime - yhour * 3600 - yminute * 60;
        system("clear");
        printf(" 玩家x遊戲時間：%02d:%02d:%02d\n",xhour,xminute,xsecond);
        printf(" 玩家y遊戲時間：%02d:%02d:%02d\n\n",yhour,yminute,ysecond);
        chessprint();
        printf(" 打入棋子請輸入H\n 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
        printf(" 玩家y輸入移動棋子的 X 座標與 Y 座標: ");
        fflush(stdout);
    }
}
void stop_cb (EV_P_ ev_io *w, int revents)
{
    if (player==1)
        xusedtime = xtime-xtimestart + xusedtime;
    else
        yusedtime = ytime-ytimestart+yusedtime;
    // for one-shot events, one must manually stop the watcher
    // with its corresponding stop function.
    ev_io_stop (EV_A_ w);
    // this causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}