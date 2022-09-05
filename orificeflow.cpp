#include "orificeflow.h"

double orificeFlow::InchToMeter(double inch)
{
    return inchToMeter * inch;
}

double orificeFlow::FToC(double fahrenheit)
{
    return (fahrenheit - 32) * 5/9;
}

double orificeFlow::M3sToCfm (double flowRate)
{
    return cfmPerCubicMeterSecond * flowRate;
}

double orificeFlow::KGsToM3s(double massFlowKGs, double airDensityKgM3)
{
    return massFlowKGs / airDensityKgM3; 
}

double orificeFlow::OrificeMassFlowKGs(double coefficientOfDischarge, double orificeRatio, 
    double expansibility, double orificeDiamterM, double fluidDensityKgM3, double deltaPa)
{
    return (coefficientOfDischarge / sqrt(1 - pow(orificeRatio, 4))) 
        * (expansibility * (M_PI / 4) * pow(orificeDiamterM, 2)) * sqrt(2 * deltaPa * fluidDensityKgM3);
}

double orificeFlow::AirPressureKPa(double elevation)
{
    //ToDo calculate atmospheric pressure from elevation
    return 101.325;
}

double orificeFlow::AirDensityKgM3(double tempCelcius, double atmosphericPressureKPa)
{ 
    //ToDo calculate density
    //For now - At 20 °C and 101.325 kPa, dry air has a density of 1.2041 kg/m3.
    return 1.2041;
}

double orificeFlow::OrificeFlowCfm(double elevationFt, double orificeDiameterInch, double airTempF, double deltaPa, double coefficient)
{
    double airDensity = AirDensityKgM3( FToC(airTempF), AirPressureKPa(0) );
    
    double flowKgs = OrificeMassFlowKGs(coefficient, orificeToPipeRatio, Expansibility(), 
        InchToMeter(orificeDiameterInch), airDensity, deltaPa);
    
    return M3sToCfm(KGsToM3s(flowKgs, airDensity));
}

//ISO 5167 Expansibility calc
double orificeFlow::Expansibility()
{
    //ϵ= 1 − (0.351 + 0.256β^4 + 0.93β^8)⋅[1−(pout/pin)^1/κ]
    //β = narrowing ratio of pipe to orifice
    //κ = heat capacity ratio = using estimated val of 1.3
    //pin intake pressure, pout discharge pressure (50pa used as constant)
    const double pin = 101350;
    const double pout = 101300;
    return 1 - (0.351 + 0.256 * pow(orificeToPipeRatio, 4) + 0.93 * pow(orificeToPipeRatio, 8) * (1 - pow((pout/pin), (1/1.3)) ));
};