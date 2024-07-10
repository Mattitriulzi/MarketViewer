#include "stock.h"


int json_parse_active(json_t* root_active)
{
    // get the most_actively_traded object and check if what the object contains is an array
    json_t *most_actively_traded = json_object_get(root_active, "most_actively_traded");
    if (!json_is_array(most_actively_traded))
    {
        perror("Root object is not an array");
        log_it("Root object is not an array");
        json_decref(root_active);
        return 4000;
    }
    // array of stock structs is declared in the header file "stock.h"
    // iterate over the object array and store the data inside our arrays of stock
    
    for (int i = 0; i < LENGTH_STOCKS; i++)
    {
        /*read the array, array contains objects (key value pairs) that must be read (with already known keys) and then stored into
        the predisposed structs, there are 20 most_active stocks theoretically ordered in their activity in the API
        Error checking checks if each pair is a string(already known type) and if not then has to print error and free both the array 
        and the original object*/
        const char *ticker, *price, *price_change, *change_percentage, *volume;

        json_t* most_active = json_array_get(most_actively_traded, i);
        if (!json_is_object(most_active))
        {
            log_it("Error when reading object array");
            json_decref(most_actively_traded);
            return 4001;
        }


        json_t *ticker_json = json_object_get(most_active, "ticker");
        if (!json_is_string((ticker_json)))
        {
            log_it("Error when reading object array");
            json_decref(root_active);
            return 4002;
        }
        
        json_t *price_json = json_object_get(most_active, "price");
        if (!json_is_string(price_json))
        {
            log_it("Error when reading object array");
            json_decref(root_active);
            return 4003;
        }

        json_t *price_change_json = json_object_get(most_active, "change_amount");
        if (!json_is_string(price_change_json))
        {
            log_it("Error when reading object array");
            json_decref(root_active);
            return 4004;
        }

        json_t *change_percentage_json = json_object_get(most_active, "change_percentage");
        if (!json_is_string(change_percentage_json))
        {
            log_it("Error when reading object array");
            json_decref(root_active);
            return 4005;
        }
        
        json_t *volume_json = json_object_get(most_active, "volume");
        if (!json_is_string(volume_json))
        {
            log_it("Error when reading object array");
            json_decref(root_active);
            return 4006;
        }


        active_stocks[i].ticker = strdup(json_string_value(ticker_json));
        check(active_stocks[i].ticker, 4007);
        active_stocks[i].price = strdup(json_string_value(price_json));
        check(active_stocks[i].price, 4008);
        active_stocks[i].price_change = strdup(json_string_value(price_change_json));
        check(active_stocks[i].price_change, 4009);
        active_stocks[i].change_percentage = strdup(json_string_value(change_percentage_json));
        check(active_stocks[i].change_percentage, 4010);
        active_stocks[i].volume = strdup(json_string_value(volume_json));
        check(active_stocks[i].volume, 4011);


    }
    return 0;
}
        
