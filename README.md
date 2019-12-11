# Unreal Assignment #9 - Final Project

Diamonick Dunn<br>
Sarah Kent<br>
Jackson Oberkirch<br>
Thomas Hill<br>
Jalon Jackson<br>

This is our submission for Assignment #9. (The Path Less Traveled)<br>
Please run game through building Visual Studio solution. 

It's a continuation of our previous project.
Video Walkthrough: https://youtu.be/b9tL_XWvfqc

## Individual Roles:
* <b>Diamonick Dunn:</b>
  * (Insert text here)
  
* <b>Sarah Kent:</b>
  * found, edited, and implemented new animations for four zombie models/skeletons (zombie spit, zombie run, zombie sprint, zombie agonize)
  * imported two new zombie models, created anim blueprints and blendspaces for new models set up all animations for new models (idle, walk, melee attack, hit reaction, death, true death)
  * worked with Jackson and Thomas to debug zombie agonize animation implementation in all ranged on rails anim blueprints
  * imported all new "farmstuff" models, renamed and reorganized models, textures, and materials as needed
  * general brainstroming with Jackson, Thomas, and Diamonick regarding implementation of mechanics (primarily some very basic psuedo code for the zombie spit projectile)
  
* <b>Jackson Oberkirch:</b>
  * Found and implemented sound effects for player damage, zombie damage, zombie death, zombie attack 
  * Found and implemented none licenced background music by placing a sound que within the level 
  * Worked on zombie encounters and zombie placement 
  * Added spotlight for every zombie type to increase visabilty and improve playability 
  * Worked with Thomas on cpp and blueprints for AI zombie, player death, enemey controller, etc. 
  * Worked with Sarah on fine tuning animations and delays 
  * Served as game tester to find bugs and anomalies
  * Recorded and uploaded video walkthrough 
  * Setup meetup times 
  
* <b>Thomas Hill:</b>
  * Refactored enemy logic into EnemyLogicComponent and EnemyAttackComponent
  * Created new enemy types: AI Enemy that moves to the player on a nav mesh, and Stationary Enemy, thats stays in place and attacks
  * Added ranged attack type for enemies, And enemy projectiles that move toward player.
  * Added damage multiplier based on consecutive shots without getting hit, and put a collision on enemies heads so they take more damage on headshot.
  * Updated Player UI to show damage multipler and the number of enemies killed.
  * Added particle effects to zombies, targets and enemy projectiles to show when they are hit.
  * Rewrote EnemyEncounter class to be able to control enemies of any type. 
  * Rewrote code to reduce coupling by using delegate events 
  
* <b>Jalon Jackson:</b>
  * (Insert text here)
  
## Description
* (Insert description here)
  
## Controls:
* Our game only uses mouse controls
* <b>Mouse: </b>Move reticle
* <b>Spacebar: </b>Reload
* <b>Left click: </b>Shoot
