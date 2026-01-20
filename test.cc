import world;
import cursescontroller;
import controller;
import cursesview;
import gameobjectcomponent;
import sprite;
import bitmaptexture;
import boxtexture;
import transform;
import event;
import pixel;
import movement;
import boxcollider;
import stopcollisionbehaviour;
import bouncecollisionbehaviour;
import inputhandler;
import spawner;
import clonablecomponent;
import vector3d;
import <string>;

class LeftRightInputHandler: public ClonableComponent<InputHandler, LeftRightInputHandler> {
        const GameObject *prototype;
        int shots = 0;
        public:
        LeftRightInputHandler(const GameObject *prototype): prototype{prototype} {}
        void handleInput(char input) override {
            Movement *movement = gameObject->getComponent<Movement>();
            Spawner *spawner = gameObject->getComponent<Spawner>();
            if(input == 'a'){
                movement->velocity = Vector3D{-1, 0, 0};
            }
            else if(input == 'd'){
                movement->velocity = Vector3D{1, 0, 0};
            }
            else if(input == ' '){
                shots++;
                gameObject->print(0, "shots " + std::to_string(shots));
                spawner->spawn(prototype);
            }
        }
    };
    

int main(){    
    
    //Press spacebar to toggle visibility of the sprite
    int HEIGHT = 20; 
    int WIDTH = 78;

    World world{78, 20, true};

    world.setController(new CursesController{});

    world.addView(new CursesView{WIDTH, HEIGHT});

    BitmapTexture texture;
    texture.addPixel(Pixel{0,0,'#'});
    texture.addPixel(Pixel{1,0,'>'});
    texture.addPixel(Pixel{2,0,'-'});

    GameObject *bullet = new GameObject("Bullet");
    bullet->addComponent(new Transform{Vector3D{0,0,0}});
    bullet->addComponent(new Sprite{'|'});
    bullet->addComponent(new Movement{Vector3D{0,1,0}, Vector3D{0,0,0}});

    GameObject *obj = new GameObject("Object1");

    obj->addComponent(new Sprite{&texture});
    obj->addComponent(new Transform{Vector3D{12, 5, 1}});
    obj->addComponent(new Movement{Vector3D{0,0.1,0}, Vector3D{0,0,0}});
    obj->addComponent(new BoxCollider{0,3,0,1});
    obj->addComponent(new BounceCollisionBehaviour{});
    obj->addComponent(new Spawner{});

    world.addGameObject(obj);
    world.play();
}
