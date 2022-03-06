#include <iostream>
#include <fstream>
using namespace std;

int baking_count = 0;
int bagel_baked = 0;
int baguette_baked = 0;
int no_request = 0;
int bakery_time = 0;
int scaling_work_time = 0;
int scaling_time = 0;
int baking_work_time = 0;
int baking_time = 0;
int rest_baking_time = 0;


int scaling_output = 9;
int mixing_output = 9;
int fermentation_output = 9;
int folding_output = 9;
int dividing_output = 9;
int rounding_output = 9;
int resting_output = 9;
int shaping_output = 9;
int profing_output = 9;
int baking_output = 9;
int cooling_output = 9;
int stocking_output = 9;
bool scalingRest = false;
bool bakingRest = false;
FILE *fout;

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
    if ((fout = fopen("test","w")) == NULL)
    {
        cout << "Cannot open ouput file" << endl;
        return -1;
    }
    if (f.is_open())
    {
        cout << "ok" << endl;
        string bake;
        int scalingRestCount = 0;
        while (getline(f, bake))
        {
            if (scalingRestCount == 10)
            {
                scalingRest = false;
            }
            
            
            if (scalingRest == true)
            {
                scalingRestCount++;
                if (bake != "No-Request")
                {
                    while (scalingRestCount < 10)
                    {
                        scalingRestCount++;
                        if (bakingRest == true && profing_output != 0)
                        {
                            Cooling(baking_output);
                            baking_output = 0;
                            bakery_time++;
                            bakingRest == false;
                        }else{
                            scaling(0);
                            bakery_time++;
                        }
                    }
                    scalingRest = false;
                }
            }

            if (bakingRest == true && profing_output != 0)
            {
                Cooling(baking_output);
                baking_output = 0;
                bakery_time++;
                bakingRest == false;
            }
            
            
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
            fprintf(fout, "\n");
        }
        f.close();
    }
    // send end message
    while (stocking_output!=8)
    {
        scaling(8);
        bakery_time++;
    }
    bakery_time--;
    
    
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
    Mixing(scaling_output);

    if (bake == 1 || bake == 2)
    {
        scaling_time++;
    }
    if (scaling_time == 1000)
    {
        scalingRest = true;
    }
    
    scaling_output = bake;
}

void Mixing(int bake){ 
    Fermentation(mixing_output); 
    mixing_output = bake;
}

void Fermentation(int bake){ 
    Folding(fermentation_output);
    fermentation_output = bake;
}

void Folding(int bake){ 
    Dividing(folding_output);
    folding_output = bake;
}

void Dividing(int bake){ 
    Rounding(dividing_output); 
    dividing_output = bake;
}

void Rounding(int bake){ 
    Resting(rounding_output); 
    rounding_output = bake;
}

void Resting(int bake){ 
    Shaping(resting_output);
    resting_output = bake;
}

void Shaping(int bake){ 
    Profing(shaping_output);
    shaping_output = bake;
}

void Profing(int bake){
    Baking(profing_output);
    profing_output = bake;
}

void Baking(int bake){
    // rest
    if (bakingRest && rest_baking_time == 0)
    {
        bakingRest = false;
        Cooling(0);
        return;
    }

    // not finished 2
    if (rest_baking_time > 0)
    {
        rest_baking_time--;
        bakingRest = false;
        baking_time++;
        Cooling(baking_output);
        baking_output = 2;
    }else if (bake == 2)
    {
        bakingRest = true;
        Cooling(0);
        rest_baking_time = 1;
    }else if(bake == 1){
        Cooling(baking_output);
        baking_output = 1;
        baking_time++;
    }else{
        Cooling(bake);
    }

    if (bake == 1)
    {
        fprintf(fout, "[10] baking Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[10] baking Bake_Baguette\n");
    }

    // need rest
    if (baking_time==10)
    {
        bakingRest = true;
        rest_baking_time = 0;
    }
}

void Cooling(int bake){ 
    Stocking(cooling_output); 
    cooling_output = bake;
}

void Stocking(int bake){ 
    stocking_output = bake;
}