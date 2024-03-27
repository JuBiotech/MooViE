Experimental Design Outcome for Isotope Tracer Experiments
---

The gold standard for quantifying intra-cellular protein turnover rates (fluxes) is 13C Metabolic Flux Analysis, which relies on
isotopic tracers. The labeling state of isotopic tracers can be expressed as binary number, where "0" stands for regular
carbon-12 isotopes and "1" for slightly heavier carbon-13 isotopes. Carefully selecting these tracers for improving 
information gain is the core objective of experimental design (ED). Information is usually quantified using information
criteria, that rate a combination of tracers with a score between 0 (not informative) to 1 (most informative). Apart 
from information gain, other objective e.g. include tracer costs.

### Multi-objective Optimal Experimental Design
Optimal experimental (O-ED) aims to find a single mixture of tracers, that maximizes all information criteria, while
minizing the total costs. Since information criteria and costs might be conflicting, this poses a multi-objective 
optimization problem that need not have a unique solution. Hence, the set of dominating solutions must be explored 
afterward. Optimal experimental design of isotope tracers poses An example of such an O-ED on *Penicillium Chrysogenum* 
for two different measurement setups is shown below. The percentages that the individual tracers have in the mixture are
taken as design variable (**input**) and several information criteria (D-criterion, E-criterion, A-criterion) and the 
total costs are taken as objectives (**output**).

<p align="center">
<div style="float: left; width: 45%; padding: 10px;">
    <img src="../_images/oed-lc.png" alt="LC-MSMS" style="width:100%">
</div>
<div class="float: left; width: 45%; padding: 10px">
    <img src="../_images/oed-gc.png" alt="GC-MS" style="width:44%">
</div>
<p style="clear: both;">
<p/>

For both measurement setups, the same kind of tracers are selected for the mixtures. The fractions, however, are 
different according to the histograms (see Glc#100001 or Glc#111111). While absolute comparison of information criteria
values is not sensible, MooViE elucidates that D-criterion and costs are on the left roughly and on the right almost
perfectly anti-correlated.

### Robust Multi-objective Experimental Design
While O-ED inherently requires to make assumptions about the actual fluxes, a more robust way to perform to ED
(R-ED) is obtained by averaging information criteria over the space of possible fluxes. An additional 
interesting objective in this case is the percentage of fluxes, which can be identified by a given design. Such
an R-ED was performed for *Streptomyces clavuligerus* by *Beyß et al., 2021* for Glycerol (Glyc) and Arginine (ARG) 
tracers. For 1,000 sample mixtures, consisting again of the fractional shares of individual tracers (**input*), averaged
D-criterion, the percentage of identifiable fluxes (coverage) and mixture costs were computed. By using MooViE with its 
GUI in an interactive fashion, the space of possible mixtures can be reduced and valuable information extracted.

<p align="center">
<div style="float: left; width: 45%; padding: 10px;">
    <img src="../_images/red-begin.png" alt="" style="width:100%">
</div>
<div class="float: left; width: 45%; padding: 10px">
    <img src="../_images/red.png" alt="" style="width:38%">
</div>
<p style="clear: both;">
<p/>

On the left, the initially generated MooViE scene is displayed. The scene is quite crowded an difficult to oversee.
Luckily, MooViE allows to interactively change it. From left to right, nuisance objective (`n_act`) and insensitive 
tracers (x-ARG) were removed. Furthermore, objective axes were constrained to only include sufficiently informative, 
covering and cheap mixtures. On the right, mixtures fall into two categories; mixtures with D-criterion around 0.9 and 
mixtures with D-criterion around 1.0. From the last category, several mixtures can be selected that still have 
considerably low costs while being highly informative.