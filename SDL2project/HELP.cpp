/*

*For moving with keyboard keys code:
///////////////////////////////////////////////////////////////////////
switch (csdl_setup->GetMainEvent()->type)
{
case SDL_KEYDOWN:
//key - keyboard data, keysym keyboard pressed or released
switch (csdl_setup->GetMainEvent()->key.keysym.sym)
{
case SDLK_a:
MoveLeft = true;
break;
case SDLK_s:
MoveDown = true;
break;
case SDLK_w:
MoveUp = true;
break;
case SDLK_d:
MoveRight = true;
break;
default:
break;
}

break;

case SDL_KEYUP:
switch (csdl_setup->GetMainEvent()->key.keysym.sym)
{
case SDLK_a:
MoveLeft = false;
break;
case SDLK_s:
MoveDown = false;
break;
case SDLK_w:
MoveUp = false;
break;
case SDLK_d:
MoveRight = false;
break;
default:
break;
}

break;
default:
break;
}
//////////////////////////////////////////////////////////////////////









*/


