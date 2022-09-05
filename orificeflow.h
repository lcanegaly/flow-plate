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

//More convenient version of Orifice flow function for imperial units, converts mass flow to volume flow.
double OrificeFlowCfm(double elevationFt, double orificeDiameterInch, double airTempF, double deltaPa, double coefficient);

double InchToMeter(double inch);
double FToC(double fahrenheit);
double M3sToCfm (double flowRate);
double KGsToM3s(double massFlowKGs, double airDensityKgM3);
double AirPressureKPa(double elevation);
double AirDensityKgM3(double tempCelcius, double atmosphericPressureKPa);

//ISO 5167 Expansibility calc
double Expansibility();

}