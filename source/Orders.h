/**
 * @brief controls and stores which orders to be executed
 */



typedef struct {
    int destFloor;


} order;

/**
 * @brief defines a struct order named order
 */

struct order order;

/**
 * @brief intializes the list of orders
 */
 
void init_orderlist();

/**
 * @brief Gives flags to floors: first_floor = 0, second_floor = 1 and so on
 */

typedef enum{first_floor, second_floor, third_floor, fourth_floor}destination;

/**
 * @brief defines a enum dest
 */

enum destination dest;


//typedef enum {Cab, Hall_Up, Hall_Down}outside_order; trenger vel ikke denne?







//functions

destination get_next_dest();
void clear_all_orders();
int add_order(order);
bool check_if_order_exist();