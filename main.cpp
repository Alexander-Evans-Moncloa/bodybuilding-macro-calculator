#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h> 

using namespace std;

class weight { //creates weight datatype for objects 
  public:
    float mass;
};

class diet { //creates diet datatype for objects
  public:
    float protein;
    float fat;
    float carbs;
    float calories;
};

int main() {

  weight metric; //creates metric unit object
  weight imperial; //creates imperial unit object
  
  diet minimum; //creates a minimum protein object
  diet ideal; //creates an ideal protein object
  diet maximum; //creates a maximum protein object
  diet survival; //creates a survival mode object
  diet cutting; //creates a cutting mode object
  diet bulking; //creates a bulking mode object
  diet maintaining; //creates a maintaining mode object

  float bf; //bodyfat percentage variable
  string preference; //stores preferred for units
  float cardio; //stores calories burnt per day extra due to cardio
  float leanmass; //stores lean mass
  float fatmass; //stores fat mass
  char mode; //stores which mode the user wants information on
  int meals; //stores number of meals per day user wants to consume
  
  cout << "Welcome to Alexander's Bodybuilding Macro Calculator.\n\nPlease start off by inputting your bodyfat percentage:\n";
  cin>>bf;
  cout<<"Would you like to enter your weight in kilograms or pounds? (kg/lb)\n";
  cin>>preference;
  if (preference=="kg"){
    cout<<"Enter how much you weigh in kilograms:\n";
    cin>>metric.mass;
    imperial.mass=metric.mass*2.204623;
    fatmass = metric.mass*(bf/100);
    leanmass = metric.mass - fatmass;
    cout<<"Your weight can be broken down into "<<(leanmass)<<"kg of lean mass and "<<(fatmass)<<"kg of fat mass.\n";
  }else if (preference=="lb"){
    cout<<"Enter how much do you weigh in pounds:\n";
    cin>>imperial.mass;
    metric.mass=imperial.mass*0.45359237;
    fatmass = metric.mass*(bf/100);
    leanmass = metric.mass - fatmass;
    cout<<"Your weight can be broken down into "<<(leanmass*2.204623)<<"lbs of lean mass and "<<(fatmass*2.204623)<<"lbs of fat mass.\n";
  }else{
    cout<<"You did not indicate your preference for weight measurement. Re-run the program please.\n";
  }

  cout<<"If you do any extra daily cardio outside resistance training, please enter it now in calories (else enter 0 or weekly cardio divided by 7):\n";
  cin>>cardio;

  //sources for these calculations in description
  survival.calories = 370+(21.6*(1-(bf/100))*metric.mass);
  maintaining.calories = (survival.calories*1.6)+cardio;
  
  minimum.protein = leanmass*2.3;
  maximum.protein = leanmass*3.1;
  
  cout<<"Are you cutting, bulking or maintaining? (c/b/m)\n";
  cin>>mode;

  switch(mode){
    case 'c':{ //CUTTING MODE
    int opt;
    cutting.calories = maintaining.calories*0.83;
    cout<<"To survive you must consume "<<survival.calories<<" calories daily.\nTo maintain bodyweight you must consume a daily amount of "<<maintaining.calories<<" calories\nTo cut you must consume "<<cutting.calories<<" calories.\n";
    ideal.protein = imperial.mass;
    cout<<"The minimum amount of daily protein recommended for a cut is "<<minimum.protein<<"g [1]. The maximum is "<<maximum.protein<<"g [2]. The ideal protein intake is "<<ideal.protein<<"g [3] (sources in description). Would you like your macros to be calculated around option 1, 2 or 3:\n";
    cin>>opt;
    switch(opt) {
    case 1:
      cutting.protein=minimum.protein;
    break;
    case 2:
      cutting.protein=maximum.protein;
    break;
    case 3:
      cutting.protein=ideal.protein;
    break;
    default:
      cout<<"You messed up a simple instruction. Redo test please.\n";
    }
    cutting.fat=imperial.mass*0.3; //for optimal hormone health (Dr Israetel, 2020)
    cutting.carbs=((cutting.calories)-(cutting.fat*9)-(cutting.protein*4))/4;
    cout<<"Your daily macros are: (drum roll please)\n\n\n"<<cutting.protein<<"g of protein\n\n"<<cutting.fat<<"g of fat\n\n"<<cutting.carbs<<"g of carbohydrates\n\n\nHow many meals a day would you like this to be spread out on? (4+ is recommended):\n";
    cin>>meals;
    cout<<"Your macros per meal are:\n\n"<<(cutting.protein/meals)<<"g of protein\n\n"<<(cutting.fat/meals)<<"g of fat\n\n"<<(cutting.carbs/meals)<<"g of carbohydrates.\n\n"<<(cutting.calories/meals)<<" calories per meal.\n\nThank you for using my calculator and good luck with your journey, I wish you the best!\n\n\nP.S. Remember, for optimal testosterone production your fats should be 50% monounsaturated, 33.33% saturated and 16.66% polyunsaturated. For simplicity, you can think it's about 1/2 olive oil, 1/3 butter and 1/6 omega 3 oils (hemp or flax seed oil)";

    
    }
    break;
    
    case 'b':{ //BULKING MODE
    float extra;
    float calories;
    bulking.calories = maintaining.calories * 1.15;
    cout<<"To survive you must consume "<<survival.calories<<" calories daily.\nTo maintain bodyweight you must consume a daily amount of "<<maintaining.calories<<" calories\nTo bulk you must consume approximately "<<bulking.calories<<" calories, but this will change depending on the protein you decide to eat.\n";
    ideal.protein = metric.mass*1.6;
    cout<<"The ideal protein intake for a bulk is "<<ideal.protein<<"g (sources in description). If you would like to eat more grams of protein per day, please enter how much more:\n";
    cin>>extra;
    bulking.protein = ideal.protein + extra; //should be 1/6th of calories
    bulking.fat = (bulking.protein*8)/9; //should be 1/3rd of calories
    bulking.carbs = ((bulking.protein*4)+(bulking.fat*9))/4; //should be half of calories
    bulking.calories = (bulking.protein*4)+(bulking.fat*9)+(bulking.carbs*4);
    cout<<"Your daily macros are: (drum roll please)\n\n\n"<<bulking.protein<<"g of protein\n\n"<<bulking.fat<<"g of fat\n\n"<<bulking.carbs<<"g of carbohydrates\n\n\nHow many daily meals would you like this to be spread out on? (3+ is recommended): Note- You are now eating "<<bulking.calories<<" calories per day. Change daily protein values if you want to consume closer to "<<(maintaining.calories*1.15)<<" calories\n";
    cin>>meals;
    cout<<"Your macros per meal are:\n\n"<<(bulking.protein/meals)<<"g of protein\n\n"<<(bulking.fat/meals)<<"g of fat\n\n"<<(bulking.carbs/meals)<<"g of carbohydrates.\n\n"<<(bulking.calories/meals)<<" calories per meal.\n\nThank you for using my calculator and good luck with your journey, I wish you the best!\n\n\nP.S. Remember, for optimal testosterone production your fats should be 50% monounsaturated, 33.33% saturated and 16.66% polyunsaturated. For simplicity, you can think it's about 1/2 olive oil, 1/3 butter and 1/6 omega 3 oils (hemp or flax seed oil)";
    }
    break;
    
    case 'm':{ //MAINTENANCE MODE
    int opt;
    cout<<"To survive you must consume "<<survival.calories<<" calories daily.\nTo maintain bodyweight you must consume a daily amount of "<<maintaining.calories<<" calories.\n";
    ideal.protein = metric.mass*1.6; 
    minimum.protein = metric.mass*1.4;
    maximum.protein = metric.mass*2;
    
    cout<<"The minimum amount of daily protein recommended for maintaining muscle is "<<minimum.protein<<"g [1]. The maximum is "<<maximum.protein<<"g [2]. The ideal protein intake is "<<ideal.protein<<"g [3] (sources in description). Would you like your macros to be calculated around option 1, 2 or 3:\n";
    cin>>opt;
    switch(opt) {
    case 1:
      maintaining.protein=minimum.protein;
    break;
    case 2:
      maintaining.protein=maximum.protein;
    break;
    case 3:
      maintaining.protein=ideal.protein;
    break;
    default:
      cout<<"You messed up a simple instruction. Redo test please.\n";
    }
    cout<<"You can choose between a range of "<<((maintaining.protein*4)/9)<<"g to "<<((maintaining.protein*8)/9)<<"g of fat. Enter ideal for you:\n";
    cin>>maintaining.fat;
    maintaining.carbs = (maintaining.calories-(maintaining.protein*4)-(maintaining.fat*9))/4; 
    cout<<"Your daily macros are: (drum roll please)\n\n\n"<<maintaining.protein<<"g of protein\n\n"<<maintaining.fat<<"g of fat\n\n"<<maintaining.carbs<<"g of carbohydrates\n\n\nHow many meals a day would you like this to be spread out on? (3+ is recommended): \n";
    cin>>meals;
    cout<<"Your macros per meal are:\n\n"<<(maintaining.protein/meals)<<"g of protein\n\n"<<(maintaining.fat/meals)<<"g of fat\n\n"<<(maintaining.carbs/meals)<<"g of carbohydrates.\n\n"<<(maintaining.calories/meals)<<" calories per meal.\n\nThank you for using my calculator and good luck with your journey, I wish you the best!\n\n\nP.S. Remember, for optimal testosterone production your fats should be 50% monounsaturated, 33.33% saturated and 16.66% polyunsaturated. For simplicity, you can think it's about 1/2 olive oil, 1/3 butter and 1/6 omega 3 oils (hemp or flax seed oil)";
    }
    break;
    default:{
    cout<<"You didn't follow simple instructions mate. Redo this test.\n";}
      
  } //closes switch case
} //closes main
