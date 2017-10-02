#ifndef COMPANIMATIONHPP
#define COMPANIMATIONHPP

#include <common.hpp>

#include <component.hpp>
#include <geometry.hpp>
#include <sprite.hpp>
#include <componentCollider.hpp>

#define COMPANIM(x)  ((CompAnim*)x.components[Component::type::t_animation])
#define COMPANIMPOINTER(x) ((CompAnim*)x->components[Component::type::t_animation])

class CompAnim : public Component{
public:
  vector<CompCollider*> colliders;
  map<int,vector<function<void(GameObject*)>>> frameFunc;
  Sprite sp;
  bool called=true;

  //public members
  CompAnim();
  CompAnim(string filename, CompCollider* temporary_collider);
  ~CompAnim();

  int get_frame_count() const;
  int get_current_frame() const;
  void set_current_frame(int frame, bool force=false);

  bool is_looped()const;

  void update(float time);
  void own(GameObject *game_object);
  void render();
  Component::type get_type()const;
};

#endif
