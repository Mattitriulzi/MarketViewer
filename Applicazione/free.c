#include "stock.h"


int free_structs(void){
    for (int i = 0; i < LENGTH_NEWS; i++){
        if ((sentiments + i)->title) free((sentiments + i)->title);
        if ((sentiments + i)->URL) free((sentiments + i)->URL);
        if ((sentiments + i)->summary) free((sentiments + i)->summary);
        if ((sentiments + i)->sentiment) free((sentiments + i)->sentiment);
        if ((sentiments + i)->tickers) free((sentiments + i)->tickers);
    }
    if(sentiments) free(sentiments);

    for (int i = 0; i < LENGTH_STOCKS; i++){
        if ((active_stocks + i)->ticker) free((active_stocks + i)->ticker);
        if ((active_stocks + i)->price) free((active_stocks + i)->price);
        if ((active_stocks + i)->price_change) free((active_stocks + i)->price_change);
        if ((active_stocks + i)->change_percentage) free((active_stocks + i)->change_percentage);
        if ((active_stocks + i)->volume) free((active_stocks + i)->volume);
    }
    if(active_stocks) free(active_stocks);

    return 0;
}