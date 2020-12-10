#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;


class Observer {
  public:
    virtual void update(int runs, int hits, int strikes, int homeruns, float win_average)=0;
};

class Subject {
  public:
    virtual void registerObserver(Observer* o)=0;
    virtual void unregisterObserver(Observer* o)=0;
    virtual void notifyObservers()=0;
};

class SportsData:public Subject {
  private:
    int runs;
    int hits;
    int strikes;
    int homeruns;
    float win_average;
    vector<Observer*> observerList;

    void notifyObservers() {
      for (int i = 0; i < observerList.size(); i++ ) {
        if (observerList.at(i) != nullptr) {
          observerList.at(i)->update(runs,hits,strikes,homeruns,win_average);
        }
      }
    }
    
    int getLatestRuns() {
      int value = rand() % 10;
      return (value > hits) ? hits : value;
    }

    int getLatestHits() {
      return (rand() % 10);
    }
    
     int getLatestStrikes() {
      int value = rand() % 10;
      return (value > hits) ? hits : value;
    }
     int getLatestHomeruns() {
      int value = rand() % 10;
      return (value > hits) ? hits : value;
    }
    

    

    float getLatestWinAverage() {
      return floorf(((float) rand() / (RAND_MAX)) * 1000) / 1000;
    }

  public:
    SportsData() {
        srand(time(0));  // Initialize random number generator.
    }

    void registerObserver(Observer* o) {
      observerList.push_back(o);
    }

    void unregisterObserver(Observer* o) {
      for (int i = 0; i < observerList.size(); i++ ) {
        if (observerList.at(i) == o) {
          observerList.erase(observerList.begin()+i);
        }
      }
    }

    // This method is used update data and displays
    void dataChanged() {
      
      //get latest data
      hits = getLatestHits();
      runs = getLatestRuns();
      strikes = getLatestStrikes();
      homeruns = getLatestHomeruns();
      win_average = getLatestWinAverage();

      notifyObservers();
    }

};

class CalcScoreDisplay: public Observer {
  private:
    float runRate;
    float homerunRate;
    float StrikeRate;

  public:
    void update(int runs, int hits, int strikes, int homeruns, float win_average) {
                         
      runRate = (hits > 0)
       ? (ceilf(((float)runs /  (float)hits)*1000)/1000) 
       : 0;
        display();
    //  homerunRate = (hits > 0)
    //   ? (ceilf(((float)runs /  (float)hits)*1000)/1000) 
      // : 0;
     // display();
    //  StrikeRate = (hits > 0)
    //   ? (ceilf(((float)runs /  (float)hits)*1000)/1000) 
    //   : 0;
    //  display();

    }

    void display() {
      cout << "\nRuns Per Hit: \n";
      cout << runRate << "\n";
    //  cout << "\n Homeruns per hit: \n";
     // cout << homerunRate<< "\n";
    //  cout << "\n Strikes per hit: \n";
     // cout << StrikeRate<< "\n";
    }
};

class CurrentScoreDisplay: public Observer {
  private:
    int runs, hits, strikes, homeruns;
    float win_average;

  public:
    void update(int new_runs, int new_hits, int new_strikes,int new_homeruns, float new_win_average) {
      runs = new_runs;
      hits = new_hits;
      strikes = new_strikes;
      homeruns = new_homeruns;
      win_average = new_win_average;
      display();
    }

    void display() {
      cout << "\nCurrent Score Display:\n";
      cout << "Runs: " << runs;
      cout << "\nHits:" << hits;
      cout << "\nStrikes: " << strikes;
      cout << "\nHomeruns: " << homeruns;
      cout << "\nWin Average: " << win_average << "\n";
    }
};

int main() {
  // create objects for display
  CalcScoreDisplay calcScoreDisplay = CalcScoreDisplay();
  CurrentScoreDisplay currentScoreDisplay = CurrentScoreDisplay();

  SportsData sportsData = SportsData();

  // register display elements
  sportsData.registerObserver(&calcScoreDisplay);
  sportsData.registerObserver(&currentScoreDisplay);

  sportsData.dataChanged();

  //remove an observer and re-run dataChanged()
  sportsData.unregisterObserver(&currentScoreDisplay);
  sportsData.dataChanged();
} 