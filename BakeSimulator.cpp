#include <iostream>
#include <fstream>
using namespace std;

// baking number
int baking_count = 0;
// number of bagels
int bagel_baked = 0;
// number of baguettes
int baguette_baked = 0;
// number of no request
int no_request = 0;

// number of bakery 
int bakery_count = 0;
// number of scaling has finished
int scaling_count = 0;
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
        while (getline(f, bake))
        {
            while (scalingRest && bake!="No-Request")
            {
                fprintf(fout, "current bakery time: %d\n", bakery_time);
                baking(0);
                bakery_time++;
            }

            while (bakingRest)
            {
                fprintf(fout, "current bakery time: %d\n", bakery_time);
                scaling(0);
                bakery_time++;
            }
            
            fprintf(fout, "current bakery time: %d\n", bakery_time);
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
        fprintf(fout, "current bakery time: %d\n", bakery_time);
        scaling(8);
        bakery_time++;
        fprintf(fout, "\n");
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
    // rest ends
    if (scaling_work_time == 0)
    {
        scalingRest = false;
    }
    
    // need a rest
    if (scaling_time == 1000)
    {
        scalingRest = true;
        scaling_work_time = -10;
        scaling_time = 0;
    }

    scaling_work_time++;

    if (bake == 1 || bake == 2)
    {
        scaling_time++;
    }
    
    Mixing(scaling_output);
    scaling_output = bake;
    if (!(bakingRest && profing_output!=0))
    {
        if (bake == 1)
        {
            fprintf(fout, "[1] sclaing Bake_Bagel\n");
        }else if (bake == 2)
        {
            fprintf(fout, "[1] sclaing Bake_Baguette\n");
        }else if (bake == 0){
            fprintf(fout, "[1] sclaing No_Request\n");
        }
        
    }
}

void Mixing(int bake){ 
    Fermentation(mixing_output); 
    if (bake == 1)
    {
        fprintf(fout, "[2] mixing Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[2] mixing Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        mixing_output = bake;
    }
}

void Fermentation(int bake){ 
    Folding(fermentation_output);
    if (bake == 1)
    {
        fprintf(fout, "[3] fermentation Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[3] fermentation Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        fermentation_output = bake; 
    }
}

void Folding(int bake){ 
    Dividing(folding_output);
    if (bake == 1)
    {
        fprintf(fout, "[4] folding Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[4] folding Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        folding_output = bake;
    }
}

void Dividing(int bake){ 
    Rounding(dividing_output); 
    if (bake == 1)
    {
        fprintf(fout, "[5] dividing Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[5] dividing Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        dividing_output = bake;
    }
}

void Rounding(int bake){ 
    Resting(rounding_output); 
    if (bake == 1)
    {
        fprintf(fout, "[6] roudning Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[6] roudning Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        rounding_output = bake;
    }
}

void Resting(int bake){ 
    Shaping(resting_output);
    if (bake == 1)
    {
        fprintf(fout, "[7] resting Bake_Bagel\n");
    }else if (bake == 2)
    {
        fprintf(fout, "[7] resting Bake_Baguette\n");
    }
    
    if (!(bakingRest && profing_output!=0))
    {
        resting_output = bake; 
    }
}