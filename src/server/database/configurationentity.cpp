#include "configurationentity.h"

// In keeping with the Wt::Dbo way of doing things as seen in tutorials and blog posts, 
//  and for the sake of brevity, all data is in public fields, and the persist implementation is in the header file.

const char* const ConfigurationEntity::TABLENAME = "Configurations";