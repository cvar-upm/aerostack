#include "droneModuleInterfaceList.h"
using namespace std;

DroneModuleInterfaceList::DroneModuleInterfaceList()
{
    for(int i=0; i<MAX_DRONEMODULES; i++)
		modules_list[i]=0;

	number_of_modules=0;


}

DroneModuleInterfaceList::~DroneModuleInterfaceList() 
{
    DestroyContent();
}

void DroneModuleInterfaceList::Delete(DroneModuleInterface *d)
{
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i] == d)
        {
            Delete(i);
            return;
        }
    }
}

void DroneModuleInterfaceList::Delete(int index)
{
    if(index<0 || index>=number_of_modules)
        return;
    else
    {
        delete modules_list[index];
        number_of_modules--;
        for(int i=index; i<number_of_modules; i++)
            modules_list[i] = modules_list[i+1];
    }
}

void DroneModuleInterfaceList::DestroyContent()
{
    for(int i=0; i<number_of_modules; i++)
        delete modules_list[i];
    number_of_modules = 0;
}

bool DroneModuleInterfaceList::Add(std::string s)
{
    bool module_found = false;
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->getModuleName() == s)
        {
            module_found = true;
            break;
        }
    }
    if(!module_found)
    {
        DroneModuleInterface* dmi = new DroneModuleInterface(s);
        Add(dmi);
    }

    return (!module_found);
}

bool DroneModuleInterfaceList::Add(DroneModuleInterface *d)
{
#ifdef DEBUG_MODE
    cout<<"Adding module..."<<endl;
#endif
    if(number_of_modules < MAX_DRONEMODULES)
    {
        modules_list[number_of_modules++] = d;
        return true;
    }
    else
        return false;
}

int DroneModuleInterfaceList::GetPosInList(DroneModuleInterface *d)
{
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i] == d)
            return i;
    }

    return 0;
}

void DroneModuleInterfaceList::Open(ros::NodeHandle &nIn)
{
    for(int i=0; i<number_of_modules; i++)
        modules_list[i]->open(nIn);
    return;
}

void DroneModuleInterfaceList::openModule(ros::NodeHandle &nIn,std::string s)
{

    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->getModuleName() == s)
            modules_list[i]->open(nIn);

    }
    return;
}

bool DroneModuleInterfaceList::moduleIsStarted(std::string s)
{
    bool response = false;
    for(int i=0; i<number_of_modules; i++)
    { 
        if(modules_list[i]->getModuleName() == s)
        {
            cout<<modules_list[i]->getModuleName()<<endl;
            if(modules_list[i]->isStarted())
            {
                cout<<"started"<<endl;
                response = true;
                break;
            }
        }

    }
    return response;
}

bool DroneModuleInterfaceList::allModuleAreStarted()
{
    bool response = true;
    for(int i=0; i<number_of_modules; i++)
    {
        if(!modules_list[i]->isStarted())
        {
            response = false;
            break;
        }
    }
    return response;
}



bool DroneModuleInterfaceList::moduleIsOnline(std::string s)
{
    bool response = false;
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->getModuleName() == s)
        {
            cout<<modules_list[i]->getModuleName()<<endl;
            if(modules_list[i]->isOnline()==1)
            {
                cout<<"online"<<endl;
                response = true;
                break;
            }
        }

    }
    return response;
}

bool DroneModuleInterfaceList::allModuleAreOnline()
{
    bool response = true;
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->isOnline()==1)
        {
            response = false;
            break;
        }
    }
    return response;
}

bool DroneModuleInterfaceList::startModule(std::string s)
{
    bool response = false;
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->getModuleName() == s)
        {
            if(modules_list[i]->isStarted()==0)
            {
                if(modules_list[i]->start())
                {
#ifdef DEBUG_MODE
                    cout<<"start module: "<<modules_list[i]->getModuleName()<<endl;
#endif
                    response = true;
                    break;
                }
            }
        }

    }
    return response;
}

bool DroneModuleInterfaceList::startAllMdoules()
{
    for(int i=0; i<number_of_modules; i++)
    {
        if(!modules_list[i]->isStarted())
            modules_list[i]->start();
    }
}

bool DroneModuleInterfaceList::stopModule(std::string s)
{
    bool response = false;
    for(int i=0; i<number_of_modules; i++)
    {
        if(modules_list[i]->getModuleName() == s)
        {
            if(modules_list[i]->isStarted())
            {
                if(modules_list[i]->stop())
                {
#ifdef DEBUG_MODE
                    cout<<"stop module: "<<modules_list[i]->getModuleName()<<endl;
#endif
                    response = true;
                    break;
                }
            }
        }

    }
    return response;
}

bool DroneModuleInterfaceList::stopAllModules()
{
    for(int i=0; i<number_of_modules; i++)
        modules_list[i]->stop();
}
std::vector<std::string> DroneModuleInterfaceList::GetNameOfDroneModules()
{
    std::vector<std::string> mod_names;
    for(int i=0;i<number_of_modules;i++)
        mod_names.push_back(modules_list[i]->getModuleName());
    return mod_names;
}




