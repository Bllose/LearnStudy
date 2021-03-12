# Imports and Setup  
First, let's make the standard imports  
``` Python
from bokeh.io import output_notebook, show
from bokeh.plotting import figure
output_notebook()
```  
This notebook uses Bokeh sample data. If you haven't downloaded it already, this can be downloaded by running the following:  
``` Python
import bokeh.sampledata
bokeh.sampledata.download()
```  

# Overview  
We've seen how Bokeh can work well with Python lists, NumPy arrays, Pandas series, etc. 
At lower levels, these inputs are converted to a Bokeh ```ColumnDataSource```. This data type is the central data source object used throughout Bokeh. 
Although Bokeh often creates them for us transparently, there are times when it is useful to create them explicitly.

In later sections we will see features like hover tooltips, computed transforms, and CustomJS interactions that make use of the ```ColumnDataSource```, 
so let's take a quick look now.  

## Creating with Python Dicts
The ```ColumnDataSource``` can be imported from ```bokeh.models```:  
``` from bokeh.models import ColumnDataSource```  

The ```ColumnDataSource``` is a mapping of column names (strings) to sequences of values. 
Here is a simple example. The mapping is provided by passing a Python ```dict``` with string keys and simple Python lists as values. 
The values could also be NumPy arrays, or Pandas sequences.

**NOTE: ALL the columns in a ```ColumnDataSource``` must always be the SAME length.**  

``` Python
source = ColumnDataSource(data={
    'x' : [1, 2, 3, 4, 5],
    'y' : [3, 7, 8, 5, 1],
})
```  
Up until now we have called functions like ```p.circle``` by passing in literal lists or arrays of data directly, 
when we do this, Bokeh creates a ```ColumnDataSource``` for us, automatically. 
But it is possible to specify a ```ColumnDataSource``` explicitly by passing it as the ```source``` argument to a glyph method. 
Whenever we do this, if we want a property (like ```"x"``` or ```"y"``` or ```"fill_color"```) to have a sequence of values, 
we pass the ***name of the column*** that we would like to use for a property:  

``` Python
p = figure(plot_width=400, plot_height=400)
p.circle('x', 'y', size=20, source=source)
show(p)
```
  
## Creating with Pandas DataFrames  
It's also simple to create ```ColumnDataSource``` objects directly from Pandas data frames. To do this, just pass the data frame to ```ColumnDataSource``` when you create it:  

``` Python  
from bokeh.sampledata.iris import flowers as df

source = ColumnDataSource(df)
```  
Now we can use it as we did above by passing the column names to glyph methods:  

``` Python  
p = figure(plot_width=400, plot_height=400)
p.circle('petal_length', 'petal_width', source=source)
show(p)  
```  

## Automatic Conversion  
If you do not need to share data sources, it may be convenient to pass dicts, Pandas ```DataFrame``` or ```GroupBy``` objects directly to glhyph methods, without explicitly creating a ```ColumnDataSource```. In this case, a ```ColumnDataSource``` will be created automatically.

``` Python  
from bokeh.sampledata.iris import flowers as df

p = figure(plot_width=400, plot_height=400)
p.circle('petal_length', 'petal_width', source=df)
show(p)
```  

# Transformations  
In addition to being configured with names of columns from data sources, glyph properties may also be configured with transform objects that represent transformations of columns. These live in the ```bokeh.transform module```. It is important to note that when doing using these objects, the tranformations occur in _the browser, not in Python_.

The first transform we look at is the ```cumsum``` transform, which can generate a new sequence of values from a data source column by cumulatively summing the values in the column. This can be usefull for pie or donut type charts as seen below.  

``` Python  
from math import pi
import pandas as pd
from bokeh.palettes import Category20c
from bokeh.transform import cumsum

x = { 'United States': 157, 'United Kingdom': 93, 'Japan': 89, 'China': 63,
      'Germany': 44, 'India': 42, 'Italy': 40, 'Australia': 35, 'Brazil': 32,
      'France': 31, 'Taiwan': 31, 'Spain': 29 }

data = pd.Series(x).reset_index(name='value').rename(columns={'index':'country'})
data['color'] = Category20c[len(x)]

# represent each value as an angle = value / total * 2pi
data['angle'] = data['value']/data['value'].sum() * 2*pi

p = figure(plot_height=350, title="Pie Chart", toolbar_location=None,
           tools="hover", tooltips="@country: @value")

p.wedge(x=0, y=1, radius=0.4, 
        
        # use cumsum to cumulatively sum the values for start and end angles
        start_angle=cumsum('angle', include_zero=True), end_angle=cumsum('angle'),
        line_color="white", fill_color='color', legend_field='country', source=data)

p.axis.axis_label=None
p.axis.visible=False
p.grid.grid_line_color = None

show(p)  
```  

The next transform we look at is the ```linear_cmap``` transform, which can generate a new sequence of colors by applying a linear colormapping to a data source column.  

``` Python  
from bokeh.transform import linear_cmap

N = 4000
data = dict(x=np.random.random(size=N) * 100,
            y=np.random.random(size=N) * 100,
            r=np.random.random(size=N) * 1.5)

p = figure()

p.circle('x', 'y', radius='r', source=data, fill_alpha=0.6,
        
         # color map based on the x-coordinate
         color=linear_cmap('x', 'Viridis256', 0, 100))

show(p)   
```  
Change the code above to use ```log_cmap``` and observe the results. Try changing ```low``` and ```high``` and specificying ```low_color``` and ```high_color```.
