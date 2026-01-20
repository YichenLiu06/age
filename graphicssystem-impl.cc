module graphicssystem;
import view;
import sprite;
import transform;
import gameobjectcomponent;
import textstatus;
import vector3d;
import <vector>;
import <memory>;
import <string>;
import <algorithm>;
import <iostream>;

GraphicsSystem::GraphicsSystem(TextStatus &textStatus): textStatus{textStatus} {}

void GraphicsSystem::addView(std::unique_ptr<View> view){
    views.push_back(std::move(view));
}

void GraphicsSystem::removeView(View *view){
    auto it = std::find_if(views.begin(), views.end(), [view](const std::unique_ptr<View> &other){return view == other.get();});
    if(it != views.end()) views.erase(it);
}

void GraphicsSystem::update(const std::vector<std::unique_ptr<GameObject>> &gameObjects){
    for(const auto &view : views){
        view->clearSprites();
        for(const auto &gameObject : gameObjects){
            if(gameObject->getComponent<Sprite>()){
                // Call drawSprite() for each Sprite at the correct position in the view
                Sprite *sprite = gameObject->getComponent<Sprite>();
                Transform *transform = gameObject->getComponent<Transform>();
                Vector3D position = transform->getPosition();
                if(!view->isInView(position.x, position.y, sprite)){
                    gameObject->setLifetime(gameObject->getLifetime()-1);
                    if(gameObject->getLifetime() <= 0)
                        gameObject->destroy();
                } 
                else{
                    gameObject->resetLifetime();
                    view->drawSprite(position.x, position.y, sprite);
                } 
            }
        }
        // Update text status
        for(int i=0; i<textStatus.getSize(); ++i){
            view->drawText(i, textStatus.getLine(i));
        }
    }   
}
