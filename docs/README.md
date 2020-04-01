# Camera Transitions
This project was developed by [Ángel González J.]([https://www.linkedin.com/in/%C3%A1ngel-gonz%C3%A1lez-jim%C3%A9nez-147174196/?locale=es_ES](https://www.linkedin.com/in/ángel-gonzález-jiménez-147174196/?locale=es_ES)) , a second year student of the [Bachelor's degrees in Video Game Design and Development at CITM/TTC](<https://www.citm.upc.edu/ing/estudis/graus-videojocs/>) as of 31/03/2020. 

This content was generated for the Project II subject under the supervision of lecturer [Ramón Santamaria](<https://www.linkedin.com/in/raysan/>).

## Table of contents
- What is a camera transition?

- Basic Transitions

- Why Apply Camera Transitions to Video Games?

  - The reasoning behind video game camera transitions.
  
  - Other uses for video game transitions.
  
- Video Game Transition Techniques

  - Manipulating geometrical forms.
  
  - Manipulating the scene's texture.
  
  - Shaders.
  
- Video Game Transition Examples

  - Basic Transitions.
  
  - Advanced Transitions.
  
  - Themed Transitions.
  
- Code Implementation

  - System Implementation
    - Scene Manager
    - Scene
    - Transition Manager
    - Transition Class
    
  - Transition Structure
  
  - The math behind the transitions.
    - Cutoff and its relation with time.
    - Linear Interpolation
    - Non-Linear Interpolation
    
  - My Transitions
  
  - Code Exercises
  
  - Links and References


## What is a camera transition?
Camera transitions are a post-production technique used to connect one shot/scene to another. With their origins being in the film industry, they are used to convey a mood, suggest the passage of time… In short, for aesthetic reasons.

## Basic Camera Transitions
### Cut
Instantly connects one shot to another. These shots normally happen at the same time.
This transition would be able to have a really parallel in video games, but, as it would go against the very reason they are implemented, cuts are ommited in video games

<img src="/images/transition_gifs/basic_transitions/Cut-Transition.gif"/>

![Cut](/images/transition_gifs/basic_transitions/Cut-Transition.gif "Aren't Cuts really cool?")

### Fade In/Out
The scene gradually turns to one colour, normally black, and comes back. Used to convey completion, the passage of a period of time and ascension  (Fade In/Out to White). The most common transition after the cut.

![Enter media description here](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/transition_gifs/basic_transitions/Fade-In-Transition.gif)

### Wipe
One shot replaces another, normally by traveling from one side of the screen to the other. Can also travel from anywhere on the screen.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/transition_gifs/basic_transitions/Wipe-Transitions.gif)

### Dissolve
Like the wipe, one shot replaces another. This time however, instead of gradually turning to a colour, the scene turns to another. Not that common nowadays.  

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/transition_gifs/basic_transitions/Dissolve-Transitions.gif)

### Zoom
The zoom is incresaed in one scene and is decreased in the next one. Wants to convey a frenetic pace or emphasize on someone or something on the screen.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/transition_gifs/basic_transitions/Zoom.gif)

## Why apply camera transitions to video games?
To put it plainly, it's to hide different elements we do not want the players to see from them. One of the main reasons can be perfectly observed in the material below. Take a look and see what happens.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Load-Time-Difference.gif)

### The reasoning behind video game camera transitions
Contrary to films, video games require time to load from one scene to another.

This process can freeze the game for a period of time, as it has just been seen in the above picture. It can take from milliseconds to, at worst, minutes. To hide this “freeze time”, camera transitions are implemented.

So, summarizing, while traditionally camera transitions are used for aesthetic purposes, in video games they serve a far more utilitarian purpose.

### Other uses for video game transitions
Although originally camera transitions had to be implemented due to purely utilitarian reasons, nowadays video games have advanced enough to be able to afford to use camera transitions for non-utilitarian purposes such as to increase the feeling of immersion or to enhancethe narrative with it. 

One great example of how to use camera transitions to bring the narrative to far higher heights is Vagrant Story (PSX). See how the camera is translated and how that creates a "reveal" moment when there was none previously.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/Camera_Translation_Hiding.gif)

Now, notice how an effect as simple as a Cut To Black can be used so cleverly. It should be noted that this segment of the game belongs to the introduction, not the end of the game.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/Cut_To_Credits.gif)


## Camera Transition Techniques
### Manipulating a geometrical form
Just “moving" geometrical shapes around, normally rectangles.

Although it is quite simple to move a rect, for example, which lowers the difficulty of making transitions with them, that simplicity is what really limits the possibilites they can offer.

Again, this technique is really simple code wise (in comparison with the following two).

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-2-Horizontal.gif)

### Manipulating the scene's texture
All the textures are blended together and manipulated.

It's a really flexible way to make transitions as textures can be modified in a great deal of ways more than "geometrical forms".

Code wise its quite complex to make transitions like the one in the example.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-8-Blender-Distortion.gif)

### Shaders
Shaders are chunks of code that are executed in the GPU. They modify the way an image is rendered.

Using shaders to make transitions has become a widespread practice due to the possibilities they bring.

#### Shader Transition Examples

**Pokeball Transition**

Original Texture:

[](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/presentation_images/Shader_Pokeball.PNG)

Transition:

[](https://github.com/BarcinoLechiguino/Camera-Transitions-
Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Shader_Transtions/Shader-Transition-1-Pokeball.gif)

Original Texture:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/presentation_images/Shader_Waves.PNG)

Transition:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Shader_Transtions/Shader-Transition-2-Waves.gif)

If you want to know more about applying shaders to camera transitions, check [Shaders Case Study - Pokémon Battle Transitions](<https://www.youtube.com/watch?v=LnAoD7hgDxw>) out, it is really easy to understand and introduces you to a lot of the basics really easily.

## VG Transition Examples
#### Disclaimer 
The majority of the transitions that will be set as examples come from Pokemon and JRPG  games, in special from battle transitions. This is due to the fact that battle transitions are as diverse as they can be, and this particular segment of camera transitions reach out to all camera transition techniques to bring really interesting transitions.

### Basic transitions
#### Fade To Black (Pokemon Fire Red / Green Leaf GBA)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Misc/Pokemon-Misc-FadeToBlack.gif)

#### Fancy Fade To Black (South Park: The Stick of Truth)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-2-Lightning.gif)

#### Wipe (Pokemon Red/Blue GBC)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-1-Circular-Wi.gif)

#### Horizontal Alternating Bars (Pokemon Red/Blue GBC)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-2-Horizontal.gif)

#### Vertical Alternating Bars (Pokemon Red/Blue GBC)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-3-Vertical-Ba.gif)

#### Camera Translation (Vagrant Story)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/Camera_Translation_To_Battle.gif)

#### Composition of Basics (Grandia II)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-5-FadeTurn.gif)

### Advanced Transitions
#### Sliding Quarters (Pokemon Red/Blue GBC)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-5-Slide-Quart.gif)

#### Texture Re-Scaling (Pokemon Red/Blue GBC)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Red_Blue/Pokemon-RedBlue-BT-4-Reduce-Text.gif)

#### Texture Manipulation: Flakes / Scales (Wild Arms 5)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-3-Flakes.gif)

#### Texture Manipulation: Blender Effect (Xenosaga Episode I)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-8-Blender-Distortion.gif)

#### Composition of Advanced (Chrono Cross)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-1-Sparks.gif)

### Themed Transitions
#### Pokemon: Battle against a Gym Leader Brock (Pokemon Fire Red / Green Leaf GBA)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Misc/Pokemon-Misc-BT-2-Brock-Battle.gif)

#### Pokemon: Battle against Zygarde (Pokemon X / Y)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/Pokemon_Transitions/Pokemon_Misc/Pokemon-Misc-BT-1-Zygarde.gif)

#### Resident Evil: Door Transition (Resident Evil PSX)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-6-RE-Door.gif)

#### Multiple Games: Mirror Break Effect (Shadow Heartsfrom the New World, Resonande of Fate, Fate/Extra, Tales of Symphonia, Dawn of the New World, Xenoblade Chronicles 2, Final Fantasy X)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/video_game_transitions/RPG_Transitions/RPG-BT-7-Broken-Mirror.gif)

# Code Implementation
## The System's core elements
### Scene Manager
The scene manager will create update and change the current_scene.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/SceneManager.PNG)

### Scene Class
Absbtract class from which all the scenes will inherit from.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/Scene.PNG)

### Transition Manager
The transition manager creates, updates and destroys the active_transition.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/TransitionManager.PNG)

### Transition Class
Will be responsible of calling the SceneManager's SwitchScene() method to switch scene when the CHANGING TRANSITION_STEP is "activated"

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/Transition.PNG)

## Transition Structure
Any given transition will be broken down in 3 steps:

- **Entering:** Step before switching scenes. Will start the transition and current_cutoff will normally start at 0.0f
- **Changing:** Step and frame at which the scene switch happens.
- **Exiting:** Step after scene switch.  Will end and delete the transition and current_cutoff will normally end at 0.0f

Depending on the transition, the current_value can go from 0.0f to 1.0f, switch scene, and then go from 1.0f to 0.0f. 

Such would be the case of the Fade To Colour transition, which the transition's rect's opacity would go from 0.0f to 255.0f, the scene would switch and then the opacity would go back to 0.0f. (current_rate * 255.0f)

On the other hand, the current_value can go from 0.0f to 1.0f, reset to 0.0f, swicth scenes, and then go from 0.0f to 1.0f again.

Such would be the case of the Wipe, which, instead of returning back like the Slide, it needs to actually cross the screen.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/TransitionStructure.PNG)

### Transition Step
There are 4 transition steps:

- **ENTERING:** Represents from the start of the transition to the scene switch. As seen in the above picture, when the transition step is ENTERING, then the Entering() method is executed.

- **CHANGING:** Represents the frame where the scenes will switch/change. As, seen in the above picture, when the transition step is CHANGING, then the Changing() method is executed.

- **EXITING:** Represents from the scene switch to the transition end. As seen in the above picture, when the transition step is EXITING, then the Exiting() method is executed.

- **NONE:** Step that should be used to prevent step errors. Not used that much.

### Entering() Method
The Entering() method will normally look like in the picture below:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_3_Solution.PNG)

### Changing() Method
The Changing() method will **ALWAYS** look like in the picture below:


![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/presentation_images/ChangingMethod.PNG)

### Exiting() Method
The Exiting() method will normally look like in the picture below:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_4_Solution.PNG)

## The mathematics behind the transitions
### Cutoff and its relation to transition time
#### The Cutoff concept
Technically, cutoff refers to the amount of screen that is being "cut off" by the transition. So it has nothing to do with **time**, for now at least. 

The cutoff value can fluctuate between 0.0f and 1.0f, representing 0,0f that the screen is not being "cut off" at all and 1.0f representing that the screen has been completely cutoff. See the 2 example pictures down below:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/presentation_images/Cutoff_Explanation.png)

Notice that, as it was mentioned before, when the cutoff value is at 0.5f, then it means that the screen has been covered halfway through:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/transition_math/Cutoff-Rate-Example.gif)

#### Cutoff/Time Implementation
The solution I propose to link the cutoff with the time is to take into account another parameter, the total time that a given transition step will take. So, in the end, two inputs are needed, the **timestep** input and the **transition time**.

The resulting equation is preety simple:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/GetCutoffRate.PNG)

The value resulting from dividing the dt by the step_duration, which the amount of time that a given transition step will take to finish, will be given the name of **Cutoff Rate**.

**Cutoff Rate Characteristics**
- Will be constant each step (given that the timestep does not fluctuate).
- If the value of the Cutoff Rate is stored in a variable each iteration, when that variable reaches a value of 1.0f (starting from 0.0f) or 0.0f (starting from 1.0f), then it means that the current transition step has ended.
- The value that defines the lifetime of a transition step will always be either 1.0f or 0.0f regardless of step_duration.

In my implementation, I named the accumulating variable current_cutoff.

#### Implementing cutoff by using shader textures.
In the case of using shaders, we can tell the GPU how to interpret a texture, so the calculation of the cutoff rate changes but the characteristics remain the same.

Instead of calculating the cutoff rate by using dt / step_duration, the texture will be assigning a float value from 0.0f to 1.0f depending on the color value of the texture's pixels.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/presentation_images/Cutoff_Rate_By_Shader.PNG)

Following the example above, when the black value is 255, then 0.0f (or transition step start) will be assigned to the variable, and when the black value is 0, the, the assigned value will be 1.0f.

### Linear Interpolation
#### Linear Interpolation Method
A linear interpolation method interpolates two values and the value returned each frame  by the interpolation will be exactly the same.

The calculus goes as shown in the picture below:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/Lerp.PNG)

#### Lerp() Characteristics
- Rate can go from 0.0f (0 %) to 1.0f (100 %) advancement per frame.
- If Lerp(0.0f, 10.0f, 1.0f), then the advancement per frame will be of 10.0f.
- Rate can also increase over time if the parameter is current_cutoff i.e.

#### Graphical Representation of Lerp()

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/transition_math/Linear-Movement.gif)

### Non-Linear Interpolation
#### Non-Linear Interpolation Method
A non-linear interpolation method interpolates two values and the value returned by the interpolation will vary each frame.

The calculus goes as shown in the picture below:

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/docs/images/system_core_elements/N_Lerp.PNG)

#### N_Lerp() Characteristics
- Rate can still go from 0.0f (0 %) to 1.0f (100 %) advancement per frame.
- While an object being interpolated by Lerp() will always have the same speed, another object interpolated by N_Lerp() can show one of two behaviours: 
  - To start with a slower velocity and end with a higher one (Ease In, Smash Out).
  - To start with a higher velocity and end with a lower one (Smash In, Ease Out). 

#### Graphical Representation of N_Lerp()

**Ease In, Smash Out**

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/transition_math/Non-Linear-Movement.gif)

**Smash In, Ease Out**

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/transition_math/Non-Linear-Easing-Out.gif)


## My Transitions
All these transitions have been implemented in C++ using SDL and STL

### Cut

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/Cut.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Cut.gif)

### Fade To Colour

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/FadeToColour.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/FadeToColor.gif)

### Slide

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/Slide.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Slide.gif)

### Wipe

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/Wipe.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Wipe.gif)

### Alternating Bars

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/AlternatingBars.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/AlternatingBars.gif)

### Expanding Bars

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/ExpandingBars.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/ExpandingBars.gif)

### Camera To Mouse

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/CameraToMouse.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/CameraToMouse.gif)

### Zoom To Mouse

[Source Code](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/master/exercises/solution/Motor2D/ZoomToMouse.cpp)

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/ZoomToMouse.gif)


## Code Exercises

Disclaimer: There are various solutions to the exercises (Lerp() & N_Lerp()), and so the solutions reflect that. In each solution there will be 2 possible solutions for each of the TODOs.

From here on it's your turn to implement some transitions. Have fun :)

## TODO 0
For TODO 0 just check out the .h files where this statement is at.

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_0.PNG)


## TODO 1

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_1_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_1_Solution.PNG">
  </p>
</details>

If you have done this TODO correctly, you should see this after pressing 1:
![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Cut.gif)

## TODO 2
From here on you will not be able to see your progress until TODO 7B

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_2_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_2_Solution.PNG">
  </p>
</details>

## TODO 3

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_3_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_3_Solution.PNG">
  </p>
</details>

## TODO 4

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_4_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_4_Solution.PNG">
  </p>
</details>

## TODO 5

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_5_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_5_Solution.PNG">
  </p>
</details>

## TODO 6A

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_6A_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_6A_Solution.PNG">
  </p>
</details>

## TODO 6B

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_6B_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_6B_Solution.PNG">
  </p>
</details>

## TODO 7A

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_7A_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_7A_Solution.PNG">
  </p>
</details>

## TODO 7B

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_7B_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_7B_Solution.PNG">
  </p>
</details>

If you have done every TODO from TODO 2 to this one, you should see this after pressing 2:
![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/FadeToColor.gif)

Congratulations! You have coded your own FadeToColour() metod. From here on out the TODOs will have their difficulty scalated quite steeply, but more challenge means more fun right? :)

## TODO 8

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_8_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_8_Solution.PNG">
  </p>
</details>

If you have completed this TODO correcly, you should see this when you LEFT CLICK:
![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/CameraToMouse.gif)

Congratulations! You can now travel all over this massive map with just a few clicks. Sit tight, after this TODO come the big boys.

## TODO 9A

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_9A_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_9A_Solution.PNG">
  </p>
</details>

## TODO 9B

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_9B_Statement.PNG)

<details> 
  <summary>Solution (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_9B_Solution.PNG">
  </p>
</details>

If you have implemented both 9A and 9B correctly, you should see this after pressing 3 and 4:
![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Slide.gif)

Congratulations! You have implemented your own Slide Transition. C'mon now, there only remain two steps to reach the summit :)

## TODO 10A

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_10A_Statement.PNG)

<details> 
  <summary>Solution I (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_10A_L_Solution.PNG">
  </p>
</details>

<details> 
  <summary>Solution II (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_10A_NL_Solution.PNG">
  </p>
</details>

## TODO 10B

![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/exercise_statements/TODO_10B_Statement.PNG)

<details> 
  <summary>Solution I (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_10B_L_Solution.PNG">
  </p>
</details>

<details> 
  <summary>Solution II (click to open)</summary>
  <p> 
     <img src="https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/solutions/TODO_10B_NL_Solution.PNG">
  </p>
</details>

If you have implemented both 10A and 10B correctly, you should see this after pressing 5 and 6:
![](https://github.com/BarcinoLechiguino/Camera-Transitions-Research/blob/v1.0/docs/images/transition_gifs/own_transitions/Wipe.gif)

Contraulations on keeping up until the end! I hope these exercises helped you in understanding how to code your very own Camera Transition System, or the at very least know how to make some simple transitions. Whichever the case, glad you reached all the way down here :)


## Links and References
#### **GIFS**

- [Basic Transitions GIFS: Cuts & Transitions 101 ](<https://www.youtube.com/watch?v=OAH0MoAv2CI>)
- [VG GIFS 1: Pokemon Red/Blue - Curiosities of battle transitions](<https://www.youtube.com/watch?v=YbDCXJ0xH2g>)
- [VG GIFS 2: Shaders Case Study - Pokémon Battle Transitions](<https://www.youtube.com/watch?v=LnAoD7hgDxw>)
- [VG GIFS 3: The Art of the JRPG Battle Transition - Desma](<https://www.youtube.com/watch?v=Bgx26kfXzlg>)



#### **Videos** 

- [Math for Game Programmers: Fast and Funky 1D Nonlinear Transformations](<https://www.youtube.com/watch?v=mr5xkf6zSzk>)

- [Timing Fight Woosh ~ Boredom Video](<https://www.youtube.com/watch?v=9RoHMNXE6YM>)
- [Transition References Video 1](<https://www.youtube.com/watch?v=BagcGilr5vc>)
- [Transition References Video 2](<https://www.youtube.com/watch?v=AxtjgdsvyLk&feature=youtu.be>)



#### **Documentation** 

- [Wikipedia: Film Transition](<https://en.wikipedia.org/wiki/Film_transition>)
- [Traditional Transitions References 1](<https://biteable.com/blog/tips/video-transitions-effects-examples/>)
- [Traditional Transition References 2](<https://www.mentalfloss.com/article/21028/5-film-transitions-worth-knowing>)
- [Traditional Transition References 3](<https://www.premiumbeat.com/blog/the-hidden-meaning-behind-popular-video-transitions/>)
- [VG Transition References Documentation 1](<http://www.davetech.co.uk/screentransitions>)
- [VG Transition References Documentation 2](<http://www.ibuprogames.com/2015/11/10/camera-transitions/>)

- [Linear Interpolation](<https://blog.bitbull.com/2019/11/13/a-lerp-smoothing-tutorial-and-example-code/>)
- [Non-Linear Interpolation](<https://gamedev.stackexchange.com/questions/14799/non-linear-interpolation>)

- [Easing Functions](<https://easings.net/en>)
- [Shaders](<https://www.webopedia.com/TERM/S/shader.html>)

