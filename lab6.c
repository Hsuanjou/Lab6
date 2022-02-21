#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 1024
struct listing
{
    int id, host_id, minimum_nights, number_of_reviews,
        calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};
struct listing getfields(char *line)
{
    struct listing item;

    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    return item;
}
void displayStruct(struct listing item)
{
    printf("ID : %d\n", item.id);
    printf("Host ID : %d\n", item.host_id);
    printf("Host Name : %s\n", item.host_name);
    printf("Neighbourhood Group : %s\n", item.neighbourhood_group);
    printf("Neighbourhood : %s\n", item.neighbourhood);
    printf("Latitude : %f\n", item.latitude);
    printf("Longitude : %f\n", item.longitude);
    printf("Room Type : %s\n", item.room_type);
    printf("Price : %f\n", item.price);
    printf("Minimum Nights : %d\n", item.minimum_nights);
    printf("Number of Reviews : %d\n", item.number_of_reviews);
    printf("Calculated Host Listings Count : %d\n",
           item.calculated_host_listings_count);
    printf("Availability_365 : %d\n\n", item.availability_365);
}
int main(int argc, char *args[])
{
    struct listing list_items[22555];
    char line[LINESIZE];
    int i, count;
    FILE *fptr = fopen("listings.csv", "r");
    if (fptr == NULL)
    {
        printf("Error reading input file listings.csv\n");
        exit(-1);
    }
    count = 0;
    while (fgets(line, LINESIZE, fptr) != NULL)
    {
        list_items[count++] = getfields(line);
    }
    fclose(fptr);
    for (i = 0; i < count; i++)
        displayStruct(list_items[i]);
    return 0;
}

int price(const void *x, const void *y)
{
    float price1 = ((struct listing *)x)->price;
    float price2 = ((struct listing *)y)->price;

    return (price1 - price2);
}
void sort_price(struct listing list_items[], int count)
{
    for (int i = 0; i < count; i++)
    {
        qsort((void *)list_items, count, sizeof(list_items[0]), price);
    }
}

int name(const void *x, const void *y)
{
    char *name1 = ((struct listing *)x)->host_name;
    char *name2 = ((struct listing *)y)->host_name;

    return strcmp(name1, name2);
}

void sort_name(struct listing list_items[], int count)
{
    for (int i = 0; i < count; i++)
    {
        qsort((void *)list_items, count, sizeof(list_items[0]), name);
    }
}
