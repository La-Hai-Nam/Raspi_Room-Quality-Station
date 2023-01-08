#ifndef SENSOR_GPIO_H
#define SENSOR_GPIO_H

//Functions from interrupt.c
int GPIO_export(int pin);                           //Export, maybe get a pin free to work?
int GPIO_unexport(int pin);                         //Unexport?
int GPIO_direction(int pin, char* direction);       //Setting direction to GPIO Pin: in/out
int GPIO_edge(int pin, char* edge);                 //??
int GPIO_read(int pin);                             //Read value
int GPIO_value(int pin, int value);                 //Set value

#endif //SENSOR_GPIO_H
