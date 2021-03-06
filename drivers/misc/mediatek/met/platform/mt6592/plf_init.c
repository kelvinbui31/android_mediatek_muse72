#include <linux/kernel.h>
#include <linux/module.h>

#include "core/met_drv.h"

static const char strTopology[] = "LITTLE:0,1,2,3|LITTLE:4,5,6,7";

extern struct metdevice met_emi;
extern struct metdevice met_smi;
extern struct metdevice met_cci400;
extern struct metdevice met_dramc;
extern struct metdevice met_thermal;
extern struct metdevice met_pmic;
#if NO_PTPOD_API == 0
extern struct metdevice met_ptpod;
#endif
#if NO_SPM_TWAM_REGISTER_HANDLER == 0
extern struct metdevice met_spmtwam;
#endif

#if NO_MET_EXT_DEV == 0
extern struct metdevice *met_ext_dev2[];
extern int met_ext_dev_lock(int flag);
extern int met_ext_dev_add(struct metdevice *metdev);
extern int met_ext_dev_del(struct metdevice *metdev);
static int met_ext_dev_max;
#endif

static int __init met_plf_init(void)
{
#if NO_MET_EXT_DEV == 0
	int i=0;
	met_ext_dev_max=met_ext_dev_lock(1);

	for(i=0; i<met_ext_dev_max; i++) {
		if (met_ext_dev2[i]!=NULL)
			met_register(met_ext_dev2[i]);
	}
#endif
	met_register(&met_emi);
	met_register(&met_smi);
	met_register(&met_cci400);
	met_register(&met_dramc);
	met_register(&met_thermal);
	met_register(&met_pmic);
#if NO_PTPOD_API == 0
	met_register(&met_ptpod);
#endif
#if NO_SPM_TWAM_REGISTER_HANDLER == 0
	met_register(&met_spmtwam);
#endif
	met_set_platform("mt6592", 1);
	met_set_topology(strTopology, 1);

	return 0;
}

static void __exit met_plf_exit(void)
{
#if NO_MET_EXT_DEV == 0
	int i=0;
	for(i=0; i<met_ext_dev_max; i++) {
		if (met_ext_dev2[i]!=NULL)
			met_deregister(met_ext_dev2[i]);
	}
	met_ext_dev_lock(0);
#endif
	met_deregister(&met_emi);
	met_deregister(&met_smi);
	met_deregister(&met_cci400);
	met_deregister(&met_dramc);
	met_deregister(&met_thermal);
	met_deregister(&met_pmic);
#if NO_PTPOD_API == 0
	met_deregister(&met_ptpod);
#endif
#if NO_SPM_TWAM_REGISTER_HANDLER == 0
	met_deregister(&met_spmtwam);
#endif
	met_set_platform(NULL, 0);
	met_set_topology(NULL, 0);
}

module_init(met_plf_init);
module_exit(met_plf_exit);
MODULE_AUTHOR("DT_DM5");
MODULE_DESCRIPTION("MET_MT6592");
MODULE_LICENSE("GPL");
