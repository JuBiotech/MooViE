The Multi-objective optimization Visualization Engine (MooViE) is developed at the Institute of Bio- and Geosciences 1 
(IBG-1) of the Forschungszentrum Jülich. MooViE is an easy-to-use tool to display multidimensional data from all 
research domains. Such data represents a mapping from multiple inputs to multiple outputs and is designed to study this
mapping. MooViE comes with a simple graphical user interface (GUI) that allows the user to interactively change which 
data is displayed and configure the style.

<p align="center">
  <img width="300" src="_images/red.png" />
</p>

MooViE accepts the data as single CSV file using **commas** as column delimiters. It expects input variables in the 
first columns and output variables after that. The first non-blank non-comment line determines the column header, in
which the input/output variables are further described. The syntax for column headers is 
- `i#<input name>[<unit>](<range begin>, <range end>)` for input headers and 
- `o#<output name>[<unit>](<range begin>, <range end>)` for outputs. 

If a column name should contain commas or square brackets, it can be masked by quotes. Units and ranges must not be
specified and can be omitted. The table cells must not be empty.