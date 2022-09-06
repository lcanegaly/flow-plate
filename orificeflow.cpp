#include "orificeflow.h"

double orifice_flow::InchToMeter(double inch) { return inch_to_meter * inch; }

double orifice_flow::FToC(double fahrenheit) {
  return (fahrenheit - 32) * 5 / 9;
}

double orifice_flow::M3sToCfm(double flow_rate) {
  return cfm_per_m3s * flow_rate;
}

double orifice_flow::KGsToM3s(double mass_flow_kg_s, double air_density_kg_m3) {
  return mass_flow_kg_s / air_density_kg_m3;
}

double orifice_flow::OrificeMassFlowKGs(
    double coefficient_of_discharge, double orifice_ratio, double expansibility,
    double orifice_diamter_m, double fluid_density_kg_m3, double delta_pa) {
  return (coefficient_of_discharge / sqrt(1 - pow(orifice_ratio, 4))) *
         (expansibility * (M_PI / 4) * pow(orifice_diamter_m, 2)) *
         sqrt(2 * delta_pa * fluid_density_kg_m3);
}

double orifice_flow::AirPressureKPa(double elevation) {
  // ToDo calculate atmospheric pressure from elevation
  return 101.325;
}

double orifice_flow::AirDensityKgM3(double temp_celcius,
                                    double atmospheric_pressure_kpa) {
  // ToDo calculate density
  // For now - At 20 °C and 101.325 kPa, dry air has a density of 1.2041 kg/m3.
  return 1.2041;
}

double orifice_flow::OrificeFlowCfm(double elevation_ft,
                                    double orifice_diameter_inch,
                                    double air_temp_f, double delta_pa,
                                    double coefficient) {
  double air_density = AirDensityKgM3(FToC(air_temp_f), AirPressureKPa(0));

  double flow_kg_s = OrificeMassFlowKGs(
      coefficient, orifice_to_pipe_ratio, Expansibility(),
      InchToMeter(orifice_diameter_inch), air_density, delta_pa);

  return M3sToCfm(KGsToM3s(flow_kg_s, air_density));
}

// ISO 5167 Expansibility calc
double orifice_flow::Expansibility() {
  //ϵ= 1 − (0.351 + 0.256β^4 + 0.93β^8)⋅[1−(pout/pin)^1/κ]
  //β = narrowing ratio of pipe to orifice
  //κ = heat capacity ratio = using estimated val of 1.3
  // pin intake pressure, pout discharge pressure (50pa used as constant)
  const double pa_in = 101350;
  const double pa_out = 101300;
  return 1 - (0.351 + 0.256 * pow(orifice_to_pipe_ratio, 4) +
              0.93 * pow(orifice_to_pipe_ratio, 8)) *
                 (1 - pow((pa_out / pa_in), (1 / 1.3)));
};