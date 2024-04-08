Visual comparison of MOO algorithms
---

Numerical algorithms are usually compared on the basis of artifical test problem. A typical process begins with the 
analysis of artificial problems and the identification of problem properties. These characteristics are then used to
compare the performance of numerical algorithms. This is exercised on the class of multi-objective optimization (MOO)
problems, which have the general form
```{math}
\min_{x \in X} \left( f_1(x), \dots, f_n(x) \right), \quad X \subseteq \mathbb{R}^m, \, Y = \mathrm{img}\left(f_1, \dots f_n\right) \subseteq \mathbb{R}^n \nonumber
```
Here, elements are mapped from the design space $X$ (**input**) to the objective space $Y$ (**output**). Solutions to
such problems are typically not unique in the sense that one element from the design space exists, that maximizes all
objectives. Hence, solutions are computed as a set of dominating solutions (Pareto set) that map to a set of 
objective vectors (Pareto front). 

### Visual summary of problem characteristics
Two artificial test problems with known solution properties were chosen from *Deb (2001)*. Both map four input variables 
that each range between 0 and 1 to three objectives. A closer characterization of these problems, namely DTLZ5 and 
DTLZ7, can be found in the [pymoo documentation](https://pymoo.org/problems/many/dtlz.html?highlight=dtlz). Most 
importantly, the solution of DTLZ5 satisfies inputs $x_3, x_4$ to be $\frac{1}{2}$ and has a continuous Pareto front. On
the other hand, the solution of DTLZ7 satisfies inputs $x_3, x_4$ to be $0$ and has a discontinuous Pareto front. For 
demonstration, both problems were solved using the well-known NSGA-II algorithm and the Pareto-optimal solutions and 
their objective values displayed using MooViE.

<p align="center">
<div style="float: left; width: 45%; padding: 10px;">
    <img src="../_images/dtlz5.png" alt="DTLZ5" style="width:100%">
</div>
<div class="float: left; width: 45%; padding: 10px">
    <img src="../_images/dtlz7.png" alt="DTLZ7" style="width:44%">
</div>
<p style="clear: both;">
<p/>

The red arrows point at the regions important for recognizing the problem characteristics. On the top, numerical 
solutions found to DTLZ5 all satisfy the conditions on the inputs $x_3, x_4$ and the continuous color distribution shows
the continuity of the Pareto front ($f_3$ is negatively correlated). On the bottom, the solutions to DTLZ7 also satify 
the conditions on the inputs and reproduce the discontinuity (determinable by the gaps on the output axes of $f_1, f_2$).

### Visual comparison of numerical solvers
Three algorithms were applied (with their default settings from [pymoo](https://pymoo.org/index.html), ergo **no 
representative benchmark**) to both test problems.

<p align="center">
    <img src="../_images/moo_alg_comparison.png" alt="MOO Comparison" style="width:75%">
<p/>

The visual comparison reveals ll algorithms satisfy the necessary conditions on the inputs $x_3, x_4$ in both cases. 
However, MOEA/D in its used configuration differs notably from the other two algorithms with regard to the Pareto front. 
It only resolves the Pareto front of DTLZ5 distinctly and less evenly populates the solution ranges for $f_1, f_2$ of 
DTLZ7. NSGA-II and SMS-EMOA yield quite similar results, but also show differences in the $x_2$ of DTLZ5, where NSGA-II
covers only the extreme values and SMS-EMOA almost the full range.