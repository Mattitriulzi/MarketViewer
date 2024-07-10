#include "stock.h"

int parseCurrencies(json_t *root, int currencyPair)
{
    if (!root) return 6001;

    json_t *parent = json_object_get(root, "Realtime Currency Exchange Rate");
    if (!json_is_object(parent)) {
        log_it("Currency JSON parent is not an object, corrupted data");
        return 6002;
    }

    json_t *fromJSON = json_object_get(parent, "2. From_Currency Name");
    if (!json_is_string(fromJSON)) {
        log_it("From Currency is not a string, corrupted data");
        return 6003;
    }

    json_t *toJSON = json_object_get(parent, "4. To_Currency Name");
    if (!json_is_string(toJSON)) {
        log_it("To Currency is not a string, corrupted data");
        return 6004;
    }

    json_t *exchangeRateJSON = json_object_get(parent, "5. Exchange Rate");
    if (!json_is_string(exchangeRateJSON)) {
        log_it("Exchange Rate is not a string, corrupted data");
        return 6005;
    }

    exchangeRates[currencyPair].fromCurrency = strdup(json_string_value(fromJSON));
    check(exchangeRates[currencyPair].fromCurrency, 6006);
    
    exchangeRates[currencyPair].toCurrency = strdup(json_string_value(toJSON));
    check(exchangeRates[currencyPair].toCurrency, 6007);

    exchangeRates[currencyPair].price = strdup(json_string_value(exchangeRateJSON));
    check(exchangeRates[currencyPair].price, 6008);

    return 0;
}
