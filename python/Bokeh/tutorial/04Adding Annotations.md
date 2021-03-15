
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

## Box Annotations  
Sometimes you might want to call out some region of the plot by drawing a shaded box. This can be done with the ```BoxAnnotation```, which is configured with the coordinate properties:

- top
- left
- bottom
- right
as well as any visual line or fill properties to control the appearance.

"Infinite" boxes can be made by leaving any of the coordinates unspecified. E.g., if ```top``` is not given, the box will always extend to the top of the plot area, regardless of any panning or zooming that happens.

Let's take a look at an example that adds a few shaded boxes to a plot:  

``` Python  
import numpy as np
from bokeh.models.annotations import BoxAnnotation

x = np.linspace(0, 20, 200)
y = np.sin(x)

p = figure(y_range=(-2, 2))
p.line(x, y)

# region that always fills the top of the plot
upper = BoxAnnotation(bottom=1, fill_alpha=0.1, fill_color='olive')
p.add_layout(upper)

# region that always fills the bottom of the plot
lower = BoxAnnotation(top=-1, fill_alpha=0.1, fill_color='firebrick')
p.add_layout(lower)

# a finite region
center = BoxAnnotation(top=0.6, bottom=-0.3, left=7, right=12, fill_alpha=0.1, fill_color='navy')
p.add_layout(center)

show(p)  
```  

## Label  
The Label annotation allows you to easily attach single text labels to plots. The position and text to display are configured as ```x```, ```y```, and ```text```:  
``` Python
Label(x=10, y=5, text="Some Label")  
```  
By default the units are in "data space" but ```x_units``` and ```y_units``` maybe set to ```"screen"``` to position the label relative to the canvas. Labels can also accept ```x_offset``` and ```y_offset``` to offset the final position from ```x``` and ```y``` by a given screen space distance.  

```Label``` objects also have standard text, line (```border_line```) and fill (```background_fill```) properties. The line and fill properties apply to a bounding box around the text:  

``` Python
Label(x=10, y=5, text="Some Label", text_font_size="12pt", 
      border_line_color="red", background_fill_color="blue")
```  
``` Python
from bokeh.models.annotations import Label
from bokeh.plotting import figure

p = figure(x_range=(0,10), y_range=(0,10))
p.circle([2, 5, 8], [4, 7, 6], color="olive", size=10)

label = Label(x=5, y=7, x_offset=12, text="Second Point", text_baseline="middle")
p.add_layout(label)

show(p)
```  
 
## LabelSet  
The ```LabelSet``` annotation allows you to create many labels at once, for instance if you want to label an entire set of scatter markers. They are similar to ```Label```, but they can also accept a ```ColumnDataSource``` as the ```source``` property, and then ```x``` and ```y``` may refer to columns in the data source, e.g. ```x="col2"``` (but may also still be fixed values, e.g. ```x=10```).  

``` Python
from bokeh.plotting import figure
from bokeh.models import ColumnDataSource, LabelSet


source = ColumnDataSource(data=dict(
    temp=[166, 171, 172, 168, 174, 162],
    pressure=[165, 189, 220, 141, 260, 174],
    names=['A', 'B', 'C', 'D', 'E', 'F']))

p = figure(x_range=(160, 175))
p.scatter(x='temp', y='pressure', size=8, source=source)
p.xaxis.axis_label = 'Temperature (C)'
p.yaxis.axis_label = 'Pressure (lbs)'

labels = LabelSet(x='temp', y='pressure', text='names', level='glyph',
                  x_offset=5, y_offset=5, source=source, render_mode='canvas')


p.add_layout(labels)

show(p)
```  

## Arrows
The ```Arrow``` annotation allows you to "point" at different things on your plot, and can be especially useful in conjuction with labels.  

For example, to create an arrow that points from ```(0,0)``` to ```(1,1)```:  
``` Python  
p.add_layout(Arrow(x_start=0, y_start=0, x_end=1, y_end=0))  
```  

This arrow will have the default [```OpenHead```](https://bokeh.pydata.org/en/latest/docs/reference/models/arrow_heads.html#bokeh.models.arrow_heads.OpenHead) arrow head at the end of the arrow. Other kinds of arrow heads include [```NormalHead```](https://bokeh.pydata.org/en/latest/docs/reference/models/arrow_heads.html#bokeh.models.arrow_heads.NormalHead) and [```VeeHead```](https://bokeh.pydata.org/en/latest/docs/reference/models/arrow_heads.html#bokeh.models.arrow_heads.VeeHead). The arrow head type can be controlled by setting the ```start``` and ```end``` properties of ```Arrow``` objects:  
``` Python
from bokeh.models.annotations import Arrow
from bokeh.models.arrow_heads import OpenHead, NormalHead, VeeHead

p = figure(plot_width=600, plot_height=600)

p.circle(x=[0, 1, 0.5], y=[0, 0, 0.7], radius=0.1,
         color=["navy", "yellow", "red"], fill_alpha=0.1)

p.add_layout(Arrow(end=OpenHead(line_color="firebrick", line_width=4),
                   x_start=0, y_start=0, x_end=1, y_end=0))

p.add_layout(Arrow(end=NormalHead(fill_color="orange"),
                   x_start=1, y_start=0, x_end=0.5, y_end=0.7))

p.add_layout(Arrow(end=VeeHead(size=35), line_color="red",
                   x_start=0.5, y_start=0.7, x_end=0, y_end=0))

show(p)
```  

## Legends  
When plots have multiple glyphs, it is desirable to include a legend to help users interpret what they see. Bokeh can generate legends easily based on the glyphs that are added.

### Simple Legends  
In the simplest case, you can simply pass a string as the ```legend_label``` argument to a glyph function:  
``` p.circle(x, y, legend_label="sin(x)") ```  
In this case Bokeh will automatically create a legend that shows a representation of that glyph, labeled by the test you provided. A full example is below.  

``` Python
import numpy as np

x = np.linspace(0, 4*np.pi, 100)
y = np.sin(x)

p = figure(height=400)

p.circle(x, y, legend_label="sin(x)")
p.line(x, 2*y, legend_label="2*sin(x)", line_dash=[4, 4], line_color="orange", line_width=2)

show(p)
```  

### Compound legends  
In the example above, we provided a different legend label to each glyph method. Sometimes, two (or more) different glyphs are used with a single data source. In this case, you can make compound legends by specifying the same legend argument to multiple glyph methods when creating a plot, for example, if you plot a ```sin``` curve with both a line and a marker, you may give them the same label to cause them to show up together in the legend:  
``` Python 
p.circle(x, y, legend_label="sin(x)")
p.line(x, y, legend_label="sin(x)", line_dash=[4, 4], line_color="orange", line_width=2)  
```  

``` Python  
# EXERCISE:  
# (1) Making a compound legend 
# (2) Position the legend using p.legend.location.  Possible values are listed at:
#     https://bokeh.pydata.org/en/latest/docs/reference/core/enums.html#bokeh.core.enums.Anchor
 
```  

## Color bars  
Color bars are especially useful if we vary the color of a glyph according to some color mapping. Bokeh color bars are configured with a color mapper and added to plots with the ```add_layout``` method:  
``` Python  
color_mapper = LinearColorMapper(palette="Viridis256", low=data_low, high=data_high)
color_bar = ColorBar(color_mapper=color_mapper, location=(0,0))
p.add_layout(color_bar, 'right')  
```  
The example below shows a complete example that also uses the color mapper to transform the glyph color.  

``` Python 
from bokeh.sampledata.autompg import autompg
from bokeh.models import LinearColorMapper, ColorBar
from bokeh.transform import transform

source = ColumnDataSource(autompg)
color_mapper = LinearColorMapper(palette="Viridis256", low=autompg.weight.min(), high=autompg.weight.max())

p = figure(x_axis_label='Horsepower', y_axis_label='MPG', tools='', toolbar_location=None)
p.circle(x='hp', y='mpg', color=transform('weight', color_mapper), size=20, alpha=0.6, source=autompg)

color_bar = ColorBar(color_mapper=color_mapper, label_standoff=12, location=(0,0), title='Weight')
p.add_layout(color_bar, 'right')

show(p)  
```  




