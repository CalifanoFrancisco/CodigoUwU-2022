class Entity : public Drawable,public Transformable {
    public:
        Sprite sprite;
        IntRect textureSize;
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
    //virtual:
};
