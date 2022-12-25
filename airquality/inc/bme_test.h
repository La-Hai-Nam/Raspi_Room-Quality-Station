#ifndef _BME_TEST_H_
#define _BME_TEST_H_


struct value{
    double temperature;
	double pressure;
	double humidity;
	double gas_resistance;
};


typedef struct value bmedata;

void bme_init(struct bme680_dev* sensor);
bmedata bme_while(struct bme680_dev* sensor, struct bme680_field_data* data);
// int bme_while(struct bme680_dev* sensor, struct bme680_field_data* data);

#endif