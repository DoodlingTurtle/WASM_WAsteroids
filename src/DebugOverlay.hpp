#ifndef REGISTER_DEBUGTYPE
#define REGISTER_DEBUGTYPE(type, tostringfnc) /* to keep the diagnostics happy */
#endif

REGISTER_DEBUGTYPE(int                              , INT   , std::to_string(*(i.d.tINT   )))
REGISTER_DEBUGTYPE(float                            , FLOAT , std::to_string(*(i.d.tFLOAT )))
REGISTER_DEBUGTYPE(double                           , DOUBLE, std::to_string(*(i.d.tDOUBLE)))
REGISTER_DEBUGTYPE(std::string                      , STR   ,                *(i.d.tSTR   ) )

#undef REGISTER_DEBUGTYPE