#pragma once
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace orificeFlow
{

constexpr double inchToMeter = 0.0254;
constexpr double cfmPerCubicMeterSecond = 2118.8799727597;
constexpr double orificeToPipeRatio = 0.001;

//ISO 5167 Orifice plate flow Equation.
double OrificeMassFlowKGs(double coefficientOfDischarge, double orificeRatio, 
    double expansibility, double orificeDiamterM, double fluidDensityKgM3, double deltaPa);
//More convienient version of Orifice flow function for imperial units, convert mass float to volume flow.
double OrificeFlowCfm(double elevationFt, double orificeDiameterInch, double airTempF, double deltaPa, double coefficient);

double InchToMeter(double inch);
double FToC(double fahrenheit);
double M3sToCfm (double flowRate);
double KGsToM3s(double massFlowKGs, double airDensityKgM3);
double AirPressureKPa(double elevation);
double AirDensityKgM3(double tempCelcius, double atmosphericPressureKPa);

//ISO 5167 Expansibility calc
static constexpr double Expansibility()
{
    //ϵ= 1 − (0.351 + 0.256β^4 + 0.93β^8)⋅[1−(pout/pin)^1/κ]
    //β = narrowing ratio of pipe to orifice
    //κ = heat capacity ratio = using estimated val of 1.3
    //pin intake pressure, pout discharge pressure (50pa used as constant)
    const double pin = 101350;
    const double pout = 101300;
    return 1 - (0.351 + 0.256 * pow(orificeToPipeRatio, 4) + 0.93 * pow(orificeToPipeRatio, 8) * (1 - pow((pout/pin), (1/1.3)) ));
};

}