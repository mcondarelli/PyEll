from ell import EllSettings


if __name__ == '__main__':
    ss = EllSettings('NETGEAR_11N.psk')
    if ss.has_group('Security'):
        psk = ss.get_string('Security', 'PreSharedKey')
        print(psk)
        pph = ss.get_string('Security', 'Passphrase')
        print(pph)

    print('-----------------------')

    for group in ss.get_groups():
        print(f'[{group}]')
        for k in ss.get_keys(group):
            print(f'{k:>15s} = {ss.get_string(group, k)}')

    def set_ipv4(net: EllSettings, ip, gw, dns=None, mask=None, bcast=None, dname=None):
        net.set_string('IPv4', 'Address', ip)
        net.set_string('IPv4', 'Gateway', gw)
        if dns:
            net.set_string('IPv4', 'DNS', dns)
        else:
            net.remove_key('IPv4', 'DNS')
        if mask:
            net.set_string('IPv4', 'Netmask', mask)
        else:
            net.remove_key('IPv4', 'Netmask')
        if bcast:
            net.set_string('IPv4', 'Broadcast', bcast)
        else:
            net.remove_key('IPv4', 'Broadcast')
        if dname:
            net.set_string('IPv4', 'DomainName', dname)
        else:
            net.remove_key('IPv4', 'DomainName')

    def set_dhcp(net:EllSettings):
        net.remove_group('IPv4')

    ss.set_string('Settings', 'AutoConnect', 'true')

    if ss.has_group('IPv4'):
        set_dhcp(ss)
    else:
        set_ipv4(ss, '192.168.7.177', '192.168.7.1', '8.8.8.8', '255.255.255.0', dname='condarelli.it')

    ss.save()
    ss.free()
