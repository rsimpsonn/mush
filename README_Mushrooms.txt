MUSHROOMS README

overview:

Hi! Welcome to our mushroom forest :)
We created new shapes to model the outer bodies of mushrooms and used L-Systems mycelium model the inner
mycelium (kinda like mushroom roots). We then combined the mushroom body and mycelium in the
SuperShroom class so that the upper part of the mycelium is encapsulated in the mushroom top and
the lower part comes out of the bottom of the mushroom stem. We also created three color schemes which
each include a different color for each part of the mushroom (top, gills, gill lines, stem, mycelium).
We create the mushrooms through a MushroomForest, which combines mushrooms of different sizes and colors.

how to use:

Once you are in the new "Mushroom Forest!" tab of the ui, you have a few options for customizing your
mushroom forest how you want it. You can choose the number of mushrooms you want generated, the
color schemes you want included (each mushroom will be randomly assigned a color scheme from the color
schemes checked), and the minimum and maximum complexity. The complexity corresponds to both the parameters
used to tesselate the shapes of the mushroom body and the level of complexity of the L-System based mycelium.
To render your mushroom forest to the screen, you then check "Enable mushroom forest" at the top. Once you have
your forest, you can also check "See top mycelium" to expose the upper part of the mycelium inside the mushroom
body.

known bugs:

- After complexity 4, the mycelium do not perfectly fit the mushroom bodies
- For mycelium view, we use the depth test on ALWAYS mode, so the positions of mushrooms get a bit missed up
- Finally, our program slows down significantly based on the number of mushrooms generated and the level of complexity chosen.
