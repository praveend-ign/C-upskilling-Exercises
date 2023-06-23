/*! virtual spi slave device driver
 *  which binds to spidev interface
 *  so that user space can access this
 *  device and perform spi data transfers
 */
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/spi/spi.h>

#include <linux/platform_device.h>

static struct spi_master *master;
static struct spi_device *spi_dev;

#define READ_TEMPERATURE	0x1
#define READ_HUMIDITY		0x2
#define READ_PRESSURE		0x3
#define WRITE_CONFIG		0x4
#define RESET_DEVICE		0x5

/*! function processes data from
 *  each spi transfer structure which
 *  are grouped to form a single
 *  spi message format
 */
static int virtspi_transfer_one(struct spi_controller *ctlr, struct spi_device *spi,
                struct spi_transfer *transfer)
{
    static unsigned short command;
    unsigned int wrconfig_value;

    pr_info("%s()\n", __func__);
    pr_info(" transfer->len == %u\n", transfer->len);

    if (transfer->rx_buf) {
        unsigned int * rx_buf = transfer->rx_buf;

	if(command == READ_TEMPERATURE) {
	/*! temperature value 27 degrees */	    
            *rx_buf = 27;
	} else if(command == READ_HUMIDITY) {
	/*! relative humidity value of 58 percent */
	    *rx_buf = 58;
	} else if(command == READ_PRESSURE) {
	/*! pressure sensor value of 42 bar */
	    *rx_buf = 42;
	} else {
	/*! write configuration and reset device
	 *  commands are just acknowledged
	 */
	    wrconfig_value = *(unsigned int *)transfer->tx_buf;
	}
    } else if(transfer->cs_change == 1) {
	command = *(unsigned short *)transfer->tx_buf;
    }

    spi_finalize_current_transfer(ctlr);

    return 0;
}

struct spi_board_info chip = {
    .modalias = "virtual_spi",
};

/*! function to probe the spi device,
 *  this function gets called when 
 *  platform device and platform driver 
 *  matches. 
 */
static int plat_probe(struct platform_device *pdev)
{
    int err = 0;

    pr_info("%s()\n", __func__);

    master = spi_alloc_master(&pdev->dev, 0);

    if (master == NULL) {
        pr_err("spi_alloc_master failed\n");
        return -ENOMEM;
    }

    master->num_chipselect = 1;

    master->transfer_one = virtspi_transfer_one;

    err = spi_register_master(master);

    if (err) {
        pr_err("spi_register_master failed\n");
        spi_master_put(master);
        return err;
    }

    spi_dev = spi_new_device(master, &chip);

    if (!spi_dev)
        err = -ENOMEM;

    if (err)
        pr_err("spi driver error\n");
    else
        pr_info("spi driver ok\n");

    return err;
}

/*! function to remove platform spi
 *  device while unloading the driver
 */
static int plat_remove(struct platform_device *pdev)
{
    pr_info("%s()\n", __func__);

    spi_unregister_master(master);

    return 0;
}

static struct platform_device * plat_device;


static struct platform_driver plat_driver = {
    .driver = {
        .name   = "virtual_spiplatform",
        .owner  = THIS_MODULE,
    },
    .probe      = plat_probe,
    .remove     = plat_remove,
};

static int __init virtspi_init(void)
{
    int err = -ENODEV;

    plat_device =  platform_device_register_simple("virtual_spiplatform",
        PLATFORM_DEVID_NONE, NULL, 0);

    if (IS_ERR(plat_device))
        return PTR_ERR(plat_device);

    err =  platform_driver_register(&plat_driver);

    if (err)
        return err;

    if (!err)
        pr_info("spi driver loaded\n");

    return err;
}

static void __exit virtspi_exit(void) {

    platform_driver_unregister(&plat_driver);
    platform_device_unregister(plat_device);

    pr_info("spi driver unloaded\n");
}


module_init(virtspi_init);
module_exit(virtspi_exit);

MODULE_LICENSE("GPL");
