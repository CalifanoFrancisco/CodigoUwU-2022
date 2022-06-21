
class Entity : public Drawable,public Transformable {
    public:
        Sprite sprite;
        IntRect textureSize;
        Entity(){}
        Entity(Texture _texture){
            //this->textureSize = IntRect(0,0,100,100);
            this->sprite      = Sprite(_texture);
            this->sprite.scale(1.f,1.f);
        }
        Entity(Texture _texture,IntRect _textureSize){
            this->textureSize = _textureSize;
            this->sprite      = Sprite(_texture,_textureSize);
        }
        IntRect getIntRect(){
          return this->textureSize;
        }
        void setTexture(Texture _texture){
            //this->sprite(_texture,this->textureSize);
        }
        void setTextureMap(Texture _texture,IntRect _intRect){
            this->sprite = Sprite(_texture,_intRect);
        }
        void scale(Vector2f e){
          this->sprite.scale(e);
        }
        void keyboardMove(){
        float ppf=1; //pixels por frame
        if(Keyboard::isKeyPressed(Keyboard::W)){this->sprite.move(this->sprite.getPosition().x+ppf,this->sprite.getPosition().y    ); }
        if(Keyboard::isKeyPressed(Keyboard::A)){this->sprite.move(this->sprite.getPosition().x    ,this->sprite.getPosition().y-ppf); }
        if(Keyboard::isKeyPressed(Keyboard::S)){this->sprite.move(this->sprite.getPosition().x-ppf,this->sprite.getPosition().y    ); }
        if(Keyboard::isKeyPressed(Keyboard::D)){this->sprite.move(this->sprite.getPosition().x    ,this->sprite.getPosition().y+ppf); }
        }

    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const {
        target.draw(this->sprite);
    }
};
