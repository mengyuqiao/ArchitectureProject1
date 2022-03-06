#include <iostream>
#include <fstream>
using namespace std;

string scalingBuffer = "";
string bakingBuffer = "";
int baking_count = 0;
int bagel_baked = 0;
int baguette_baked = 0;
int no_request = 0;
int bakery_time = 0;
int scaling_work_time = 0;
int baking_work_time = 0;
int baking_time = 0;
int rest_baking_time = 0;
bool getEnd = true;
int output = 0;

void scaling(int bake);
void Mixing(int bake);
void Fermentation(int bake);
void Folding(int bake);
void Dividing(int bake);
void Rounding(int bake);
void Resting(int bake);
void Shaping(int bake);
void Profing(int bake);
void Baking(int bake);
void Cooling(int bake);
void Stocking(int bake);

int main()
{
    //get input
    fstream f;
    f.open("trace1", ios::in);
    getEnd = true;
    if (f.is_open())
    {
        string bake;
        while (getline(f, bake))
        {
            while (!getEnd){}
            getEnd = false;
            if (bake == "Bake-Bagel")
            {
                scaling(1);
                baking_count++;
                bagel_baked++;
            }else if (bake == "Bake-Baguette")
            {
                scaling(2);
                baking_count++;
                baguette_baked++;
            }else{
                scaling(0);
                no_request++;
            }
            bakery_time++;
        }
        f.close();
    }
    while (output!=-1)
    {
        while (!getEnd){}
        getEnd = false;
        scaling(-1);
        bakery_time++;
    }
    
    
    //output formats
    printf("\nBaking count: %d\n", baking_count);
    printf(" - Bagel baked: %d\n", bagel_baked);
    printf(" - Baguette baked: %d\n", baguette_baked);
    printf("No request: %d\n", no_request);

    printf("\nHow many minutes to bake: %d\n", bakery_time);

    double performance = (double)(bagel_baked + baguette_baked)/(double)bakery_time;

    printf("\nPerformance (bakes/minutes): %.2f\n", performance);

    return 0;
}

void scaling(int bake){
    if (scaling_work_time==1000)
    {
        scaling_work_time = -10;
    }
    scaling_work_time++;
    if (scaling_work_time > 0)
    {
        int b = scalingBuffer[0];
        scalingBuffer.erase(0,1);
        // while (b == 0 && scalingBuffer.size() > 0)
        // {
        //     b = scalingBuffer[0];
        //     scalingBuffer.erase(0,1);
        // }
        Mixing(b);
    }else{
        Mixing(0);
    }
}

void Mixing(int bake){ Fermentation(bake); }

void Fermentation(int bake){ Folding(bake); }

void Folding(int bake){ Dividing(bake); }

void Dividing(int bake){ Rounding(bake); }

void Rounding(int bake){ Resting(bake); }

void Resting(int bake){ Shaping(bake); }

void Shaping(int bake){ Profing(bake); }

void Profing(int bake){ 
    bakingBuffer.append(to_string(bake));
    Baking(bake); 
}

void Baking(int bake){
    // still baking
    if ( rest_baking_time > 0)
    {
        rest_baking_time--;
        baking_time++;
        Cooling(0);
        return;
    }
    // need a rest
    if (baking_time==10)
    {
        baking_work_time = -1;
        baking_time = 0;
    }
    baking_work_time++;
    // need a new work to do
    if (baking_work_time > 0)
    {
        int b = 0;
        if (rest_baking_time <= 0)
        {
            b = bakingBuffer[0];
            bakingBuffer.erase(0,1);
            // if get empty, just go after until find a job or the buffer is empty
            // while (b == 0 && bakingBuffer.size() > 0)
            // {
            //     b = bakingBuffer[0];
            //     bakingBuffer.erase(0,1);
            // }
            // if has a job to do, just do it
            if (b > 0)
            {
                rest_baking_time += b;
                rest_baking_time--;
                if (rest_baking_time == 0)
                {
                    baking_time++;
                }
            }
            Cooling(b);
            return;
        }
    }
}

void Cooling(int bake){ Stocking(bake); }

void Stocking(int bake){ 
    if (bake == -1)
    {
        printf("%d", bake);
    }
    
    output = bake;
    getEnd = true;
}