
``` Python  
from bokeh.io import output_notebook, show
from bokeh.plotting import figure
output_notebook()  
```  

# Overview  
Sometimes we want to add visual cues (boundary lines, shaded regions, labels and arrows, etc.) to our plots to call out some feature or other. Bokeh has several annotation types available for uses like this. 
Typically to add annotations we create the "low level" annotation object directly, and add it to our plot using ```add_layout```. Let's take a look at some specific examples.  

## Spans  
```Spans``` are "infinite" vertical or horizonal lines. When creating them, you specify the ```dimension``` that should be spanned (i.e., ```width``` or ```height```), 
any visual line properties for the appearance, and the location along the dimension where the line should be drawn. 
Let's look at an example that adds two horizontal spans to a simple plot:  

``` Python 
import numpy as np
from bokeh.models.annotations import Span

x = np.linspace(0, 20, 200)
y = np.sin(x)

p = figure(y_range=(-2, 2))
p.line(x, y)

upper = Span(location=1, dimension='width', line_color='olive', line_width=4)
p.add_layout(upper)

lower = Span(location=-1, dimension='width', line_color='firebrick', line_width=4)
p.add_layout(lower)

show(p)
```
