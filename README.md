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
  * Expanded the level by approximately 250% as well as crafted the rest of the level. 
  * Imported free assets (fire effects, grass foilage, and a tree) from the UE4 Marketplace.
  * Managed zombie placement, enemy encounters, and spline path movement.
  * Created a burning zombie. The only difference is that it runs pretty fast towards the player.
  * Made a new bridge static mesh.
  * Organized the world outliner and Content folder.
  * Served as level designer for the project.
  
* <b>Sarah Kent:</b>
  * Found, edited, and implemented new animations for four zombie models/skeletons (zombie spit, zombie run, zombie sprint, zombie agonize)
  * Imported two new zombie models, created anim blueprints and blendspaces for new models set up all animations for new models (idle, walk, melee attack, hit reaction, death, true death)
  * Worked with Jackson and Thomas to debug zombie agonize animation implementation in all ranged on rails anim blueprints
  * Imported all new "farmstuff" models, renamed and reorganized models, textures, and materials as needed
  * General brainstroming with Jackson, Thomas, and Diamonick regarding implementation of mechanics (primarily some very basic psuedo code for the zombie spit projectile)
  
* <b>Jackson Oberkirch:</b>
  * Found and implemented sound effects for player damage, zombie damage, zombie death, zombie attack 
  * Found and implemented none licenced background music by placing a sound que within the level 
  * Worked on zombie encounters and zombie placement 
  * Added spotlight for every zombie type to increase visibilty and improve playability 
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
* Our game is based on on-rail shooters where the camera automatically scrolls, and you're limited by your current field of view.
* Your health starts at 5. Once it reaches 0, you can either play the game again or quit the game.
* Once you're out of ammo, it's best to reload to continue shooting. You can reload at any time.
* In the previous project, the level didn't have much flare to make the level look convincing. In this project, we added believable fire effects, grass foilage, a barn, a chapel, and some big trees to create a zombie-infested environment.
* There are 11 stops where you have to shoot at the active zombies to proceed.
* Get a headshot to kill zombies faster. The accuracy of the headshot collision is fairly generous.
* The UI contains the player's health, gun ammo, number of zombies killed, and a damage multiplier.
  
## Controls:
* Our game only uses mouse controls
* <b>Mouse: </b>Move reticle
* <b>Spacebar: </b>Reload
* <b>Left click: </b>Shoot
