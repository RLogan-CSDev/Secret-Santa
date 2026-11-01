# Storyboard: Secret Santa Application
This document serves as a visual to map the page layouts and the relationships between each
page, diagraming the interactivity for the Secret Santa application. Outlining the flow between
the initial setup screen to the final assignment window facilitates a blueprint for the
application's architecture and user experience.

## Screen 1: Setup
![Setup Screen Wireframe](assets/screen1_wireframe.svg)

## Screen 2: Adding Players
![Adding Players Screen Wireframe](assets/screen2_wireframe.svg)
#### **Note**: Potential UX = one person adds all players to Santa bag vs. each player individually adding themselves

## Screen 3: Adding Gifts / Partners
![Adding More Screen Wireframe](assets/screen3_wireframe.svg)

## Screen 4: Secret Santa Assignment
![Assignment Screen Wireframe](assets/screen4_wireframe.svg)

## Screen 5: Confirmation
![Confirmation Screen Wireframe](assets/screen5_wireframe.svg)
#### **Note**: To make sure all gifts are added before moving on to assignment phase

### Interactivity Diagram
**Screen 1** -> **Screen 2** -> **Screen 3** -> **Screen 5** (Repeatedly call back to *Screen 3* until condition is met) -> **Screen 4**