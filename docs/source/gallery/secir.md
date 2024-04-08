Sensitivity of compartment models
---

With data from [*Kühn et al. (2021)*](http://dx.doi.org/10.1016/j.mbs.2021.108648) and
[*Koslow et al. (2022)*](http://dx.doi.org/10.1371/journal.pcbi.1010054), parameters of a state-of-the-art SECIR model 
were analyzed regarding their impact on the total number of deaths. Specifically, a result focussed on two parameters,
transmission probability on contact (TP) and deaths per critical (DpC), was obtained. It was found that the sensitivity
to changes in DpC is high and low to changes in TP.

<p align="center">
    <img style="width: 50%" src="../_images/secir.png">
<p/>

The above MooViE scene shows the relationship between the two parameters TP and DpC. High values of DpC lead to high
numbers of deaths and low values of DpC lead to to low numbers of deaths. Both high and low numbers of TP can lead to
low or high numbers of deaths.