

//
typedef struct {
    int destFloor;
} Order;
 


//enum - switch



typedef enum{first_floor, second_floor, third_floor, fourth_floor}destination;

typedef enum {Cab, Hall_Up, Hall_Down}outside_order;





typedef struct {
    Orders orders[8];

} Orders;



//functions

void init();
destination get_next_dest();
bool clear_all_orders();
int add_order(Order Order);
bool check_if_order_exist();