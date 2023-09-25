# PhysicsEngine

This will be a (hopefully) fully finished physics engine when complete. Most of the structure for the engine is developed, but the formulas and visuals are still on the way. The main goal of this is to be able to test and add different physics features over time while visualizing the entities moving. 

Goals:<br>
Bodies: Rigidbody and Softbody along with transforms for those(like rotation, scaling) <br>
Colliders: box, sphere and mesh<br>
Springs: maybe, if we get an ode working well using rk4<br>
<br>
There hasn't been a lot of progress on this repo due to my physics class not getting to collisions yet. The main issues I am having is figuring out the instantaneous forces on an object during a collision. Falling due to gravity and constant acceleration motion is easy to simulate with the kinematic equations. My method of integrating acceleration to get velocity and velocity to get position does work, but the main holdup is figuring out what the forces are during a colision or bouncing. Also, RenderProject has come very far from when this project was started so I will have to do an update with that import
