#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int getAccuracy(vector<vector<double>>vect);
int leaveOneOut(vector<vector<double>>vect, vector<int>currSet, int featToAdd);
int makeChoice();
void featureSearch(vector<vector<double>>vect);
void reverseSearch(vector<vector<double>>vect);
int revLeaveOne(vector<vector<double>>vect, vector<int>currSet);
vector<double>parseLine(string line);
vector<double>parseLineL(string line);

int main()
{
    int choiceRet;
    cout << "Welcome to my feature selection algorithm\n";
    do {
        choiceRet = makeChoice();
    } while (choiceRet != 0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

int getAccuracy(vector<vector<double>>vect)
{
    vector<double>objToClassify;
    vector<double>tmp;
    double labelObjToClass;
    float accuracy = 0;
    double nearNeighLabel = DBL_MAX;
    int correctNum = 0;
    vector<double>testVect;
    for (unsigned int i = 1; i < vect[i].size(); i++) {
        testVect.push_back(i);
    }
    for (unsigned int i = 0; i < vect.size(); i++) {
        labelObjToClass = vect[i][0];
        for (unsigned int j = 0; j < testVect.size(); j++) {
            objToClassify.push_back(vect[i][testVect[j]]);
        }
        double nearNeighDist = DBL_MAX;
        double nearNeighLoc = DBL_MAX;
        for (unsigned int j = 0; j < vect.size(); j++) {
            if (j != i) {
                for (int k = 0; k < testVect.size(); k++) {
                    tmp.push_back(pow((vect[j][testVect[k]] - objToClassify[k]), 2));
                }

                double sum = 0;
                for (int k = 0; k < tmp.size(); k++) {
                    sum += tmp[k];
                }
                double dist = sqrt(sum);

                tmp.clear();

                if (dist < nearNeighDist) {
                    nearNeighDist = dist;
                    nearNeighLoc = j;
                    nearNeighLabel = vect[j][0];
                }
            }
        }
        if (labelObjToClass == nearNeighLabel) {
            correctNum++;
        }
        objToClassify.clear();
    }
    //cout << "correctNum: " << correctNum << "\n";
    //cout << "vect.size(): " << vect.size() << "\n";
    accuracy = (correctNum * 100.f) / vect.size();
    return accuracy;


    //cout << "Looping over i, at the " << i+1 << " location...\n";
        //cout << "The " << i + 1 << "th object is in class " << labelObjToClass << "\n";
        //cout << "It's nearest neighbor is " << nearNeighLoc << " Which is in class " << nearNeighLabel << "\n";

}

int leaveOneOut(vector<vector<double>> vect, vector<int> currSet, int featToAdd)
{
    vector<double>objToClassify;
    vector<double>tmp;
    double labelObjToClass;
    float accuracy = 0;
    double nearNeighLabel = DBL_MAX;
    int correctNum = 0;
    int tmpSize;

    currSet.push_back(featToAdd);
    for (unsigned int i = 0; i < vect.size(); i++) {
        labelObjToClass = vect[i][0];
        for (unsigned int j = 0; j < currSet.size(); j++) {
            objToClassify.push_back(vect[i][currSet[j]]);
        }
        double nearNeighDist = DBL_MAX;
        double nearNeighLoc = DBL_MAX;
        for (unsigned int j = 0; j < vect.size(); j++) {
            if (j != i) {
                for (int k = 0; k < currSet.size(); k++) {
                    tmp.push_back(pow((vect[j][currSet[k]] - objToClassify[k]), 2));
                }
                
                double sum = 0;
                for (int k = 0; k < tmp.size(); k++) {
                    sum += tmp[k];
                }
                double dist = sqrt(sum);
                
                tmp.clear();

                if (dist < nearNeighDist) {
                    nearNeighDist = dist;
                    nearNeighLoc = j;
                    nearNeighLabel = vect[j][0];
                }
            }
        }
        if (labelObjToClass == nearNeighLabel) {
            correctNum++;
        }
        objToClassify.clear();
    }
    accuracy = (correctNum * 100.f) / vect.size();
    return accuracy;
}

int makeChoice()
{
    ifstream dataset;
    vector<vector<double>>vect;
    string line;
    int choice; 
    int myCount;

    cout << "Please select which dataset you're working with\n-(1) SMALL --Ver_2_CS170_Fall_2021_Small_data__80.txt\n-(2) LARGE --Ver_2_CS170_Fall_2021_LARGE_data__80.txt\n-(3) Quit\n";
    cin >> choice;
    switch (choice) {
    case 1:
        dataset.open("C:\\Users\\Ismael Moreno\\source\\repos\\AIPuzzle\\AIPuzzle\\Ver_2_CS170_Fall_2021_Small_data__80.txt");
        while (getline(dataset, line)) {
            vect.push_back(parseLine(line));
        }
        break;
    case 2:
        dataset.open("C:\\Users\\Ismael Moreno\\source\\repos\\AIPuzzle\\AIPuzzle\\Ver_2_CS170_Fall_2021_LARGE_data__80.txt");
        while (getline(dataset, line)) {
            vect.push_back(parseLineL(line));
        }
        break;
    case 3:
        cout << "Thank you for using this program, GoodBye\n";
        return 0;
        break;
    default:
        cout << "Sorry not a valid choice";
        makeChoice();
        break;
    }
    cout << "Please select the type of algorithm you want to run:\n\n(1) Forward Selection\n(2) Backwards Elimination\n";
    cin >> choice;
    switch (choice) {
    case 1:
        featureSearch(vect);
        break;
    case 2:
        reverseSearch(vect);
        break;
    }
    dataset.close();
    return 1;
}

void featureSearch(vector<vector<double>> vect)
{
    int bestSoFar = 0;
    int highestAcc = 0;
    int feature = 0;
    vector<int>setOfFeatures;
    vector<int>setCopy;
    bool repeat = false;
    int accuracy = 100;
    cout << vect.size() << endl;
    cout << vect[1].size() << endl;
    for (unsigned int i = 1; i < vect[i].size(); i++) {
        cout << "on the " << i << "th level of the search tree...\n";
        bestSoFar = 0;
        for (unsigned int j = 1; j < vect[i].size(); j++) {
            for (unsigned int k = 0; k < setOfFeatures.size(); k++) {
                if (j == setOfFeatures[k]) {
                    repeat = true;
                }
            }
            if (repeat) {
                repeat = false;
                continue;
            }
            cout << "--considering adding the " << j << " feature...\n";
            accuracy = leaveOneOut(vect, setOfFeatures, j);
            cout << "accuracy: " << accuracy << "%\n";
            if (accuracy > bestSoFar) {
                bestSoFar = accuracy;
                feature = j;
            }
        }
        setOfFeatures.push_back(feature);

        if (bestSoFar > highestAcc) {
            highestAcc = bestSoFar;
            setCopy = setOfFeatures;
        }
        cout << "On level " << i << " I added feature " << feature << " to current set, for an accuracy of " << bestSoFar << "%\n\n\n";
    }
    cout << "The highest accuracy was " << highestAcc << " % with features <";
    for (unsigned int i = 0; i < setCopy.size(); i++) {
        cout << setCopy[i];
        if (i != setCopy.size() - 1) {
            cout << ",";
        }
    }
    cout << ">\n\n\n";
}

void reverseSearch(vector<vector<double>> vect)
{
    int bestSoFar = 0;
    int highestAcc = 0;
    int feature = 0;
    vector<int>setOfFeatures;
    vector<int>setOfFeatCP;
    for (unsigned int i = 1; i < vect[1].size(); i++) {
        setOfFeatures.push_back(i);
    }
    cout << "numFeateures: " << setOfFeatures.size() << endl;
    vector<int>setCopy;
    bool repeat = false;
    int accuracy = 100;
    cout << vect.size() << endl;
    cout << vect[1].size() << endl;
    for (unsigned int i = 1; i < vect[i].size(); i++) {
        cout << "on the " << i << "th level of the search tree...\n";
        bestSoFar = 0;
        for (unsigned int j = 0; j < setOfFeatures.size(); j++) {
            cout << "--considering removing the " << setOfFeatures[j] << " feature...\n";
            for (unsigned int k = 0; k < setOfFeatures.size(); k++) {
                if (setOfFeatures[j] != setOfFeatures[k]) {
                    setOfFeatCP.push_back(setOfFeatures[k]);
                }
            }
            accuracy = revLeaveOne(vect,setOfFeatCP);
            cout << "accuracy: " << accuracy << "%\n";
            setOfFeatCP.clear();

            if (accuracy > bestSoFar) {
                bestSoFar = accuracy;
                feature = setOfFeatures[j];
            }
        }
        for (unsigned int k = 0; k < setOfFeatures.size(); k++) {
            if (setOfFeatures[k] != feature) {
                setOfFeatCP.push_back(setOfFeatures[k]);
            }
        }
        setOfFeatures = setOfFeatCP;
        setOfFeatCP.clear();

        if (bestSoFar > highestAcc) {
            highestAcc = bestSoFar;
            setCopy = setOfFeatures;
        }
        cout << "On level " << i << " I removed feature " << feature << " to current set for an accuracy of " << bestSoFar <<"%\n\n\n";
    }
    cout << "The highest accuracy was " << highestAcc << " % with features <";
    for (unsigned int i = 0; i < setCopy.size(); i++) {
        cout << setCopy[i];
        if (i != setCopy.size() - 1) {
            cout << ",";
        }
    }
    cout << ">\n\n\n";
}

int revLeaveOne(vector<vector<double>> vect, vector<int> currSet)
{
    vector<double>objToClassify;
    vector<double>tmp;
    double labelObjToClass;
    float accuracy = 0;
    double nearNeighLabel = DBL_MAX;
    int correctNum = 0;
    int tmpSize;

    for (unsigned int i = 0; i < vect.size(); i++) {
        labelObjToClass = vect[i][0];
        for (unsigned int j = 0; j < currSet.size(); j++) {
            objToClassify.push_back(vect[i][currSet[j]]);
        }
        double nearNeighDist = DBL_MAX;
        double nearNeighLoc = DBL_MAX;
        for (unsigned int j = 0; j < vect.size(); j++) {
            if (j != i) {
                for (int k = 0; k < currSet.size(); k++) {
                    tmp.push_back(pow((vect[j][currSet[k]] - objToClassify[k]), 2));
                }

                double sum = 0;
                for (int k = 0; k < tmp.size(); k++) {
                    sum += tmp[k];
                }
                double dist = sqrt(sum);

                tmp.clear();

                if (dist < nearNeighDist) {
                    nearNeighDist = dist;
                    nearNeighLoc = j;
                    nearNeighLabel = vect[j][0];
                }
            }
        }
        if (labelObjToClass == nearNeighLabel) {
            correctNum++;
        }
        objToClassify.clear();
    }
    accuracy = (correctNum * 100.f) / vect.size();
    return accuracy;
}

vector<double>parseLine(string line)
{
    string tmpstr = line;
    int place = 2;
    vector<double>tmpVect;
    for (unsigned int i = 0; i < 11; i++) {
        tmpVect.push_back(stod(tmpstr.substr(place, 16)));
        place += 16;
    }
    return tmpVect;
}

vector<double> parseLineL(string line)
{
    string tmpstr = line;
    int place = 2;
    vector<double>tmpVect;
    for (unsigned int i = 0; i < 51; i++) {
        tmpVect.push_back(stod(tmpstr.substr(place, 16)));
        place += 16;
    }
    return tmpVect;
}

