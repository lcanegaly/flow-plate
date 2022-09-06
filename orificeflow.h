#pragma once
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace orifice_flow {
constexpr double inch_to_meter = 0.0254;
constexpr double cfm_per_m3s = 2118.8799727597;
constexpr double orifice_to_pipe_ratio = 0.001;

// ISO 5167 Orifice plate flow Equation.
double OrificeMassFlowKGs(double coefficient_of_discharge, double orifice_ratio,
                          double expansibility, double orifice_diamter_m,
                          double fluid_density_kg_m3, double delta_pa);

// More convenient version of Orifice flow function for imperial units, converts
// mass flow to volume flow.
double OrificeFlowCfm(double elevation_ft, double orifice_diameter_inch,
                      double air_temp_f, double delta_pa, double coefficient);
double InchToMeter(double inch);
double FToC(double fahrenheit);
double M3sToCfm(double flow_rate);
double KGsToM3s(double mass_flow_kg_s, double air_density_kg_m3);
double AirPressureKPa(double elevation);
double AirDensityKgM3(double temp_celcius, double atmospheric_pressure_kpa);

// ISO 5167 Expansibility calc
double Expansibility();
}  // namespace orifice_flow